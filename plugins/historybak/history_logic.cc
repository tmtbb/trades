//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "history/history_logic.h"
#include "history/history_proto_buf.h"
#include "history/operator_code.h"
#include "history/errno.h"
#include "history/schduler_engine.h"
#include "logic/swp_infos.h"
#include "comm/comm_head.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/history/history_config.xml"

#define TIME_DISTRIBUTION_TASK 10001

namespace history_logic {

Historylogic *Historylogic::instance_ = NULL;

Historylogic::Historylogic() {
  if (!Init())
    assert(0);
}

Historylogic::~Historylogic() {
  if (history_db_) {
    delete history_db_;
    history_db_ = NULL;
  }
  history_logic::HistoryEngine::FreeSchdulerManager();
  history_logic::HistoryEngine::FreeHistoryEngine();
}

bool Historylogic::Init() {
  bool r = false;
  manager_schduler::SchdulerEngine* (*schduler_engine)(void);
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  history_db_ = new history_logic::HistoryDB(config);
  history_logic::HistoryEngine::GetSchdulerManager()->InitDB(history_db_);
  history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryTradesData();
  history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryRechargeData();
  history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryWithDrawals();

  std::string schduler_library = "./data_share.so";
  std::string schduler_func = "GetManagerSchdulerEngine";
  schduler_engine = (manager_schduler::SchdulerEngine* (*)(void))
  logic::SomeUtils::GetLibraryFunction(
  schduler_library, schduler_func);schduler_engine_
  = (*schduler_engine)();
  if (schduler_engine_ == NULL)
    assert(0);

  history_logic::HistoryEngine::GetSchdulerManager()->InitSchdulerEngine(
      schduler_engine_);
  return true;
}

Historylogic *Historylogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Historylogic();
  return instance_;
}

void Historylogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Historylogic::OnHistoryConnect(struct server *srv, const int socket) {
  std::string ip;
  int port;
  logic::SomeUtils::GetIPAddress(socket, ip, port);
  LOG_MSG2("ip {%s} prot {%d}", ip.c_str(), port);
  return true;
}

bool Historylogic::OnHistoryMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket %d", socket);
    send_error(socket, ERROR_TYPE, ERROR_TYPE, FORMAT_ERRNO);
    return false;
  }

  switch (packet->operate_code) {
    case R_HISTORY_TRADES: {
      OnHistoryTrades(srv, socket, packet);
      break;
    }
    case R_HISTORY_RECHARGE: {
      OnHistoryRecharge(srv, socket, packet);
      break;
    }

    case R_HISOTRY_WITHDRAWALS: {
      OnHistoryWithdrawals(srv, socket, packet);
      break;
    }

    case R_HISTORY_TRADES_HANDLE: {
      OnHistoryTradesHandle(srv, socket, packet);
      break;
    }
    default:
      break;
  }
  return true;
}

bool Historylogic::OnHistoryClose(struct server *srv, const int socket) {
  return true;
}

bool Historylogic::OnBroadcastConnect(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  return true;
}

bool Historylogic::OnBroadcastMessage(struct server *srv, const int socket,
                                      const void *msg, const int len) {

  return true;
}

bool Historylogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Historylogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
    if (srv->add_time_task != NULL) {
      srv->add_time_task(srv, "history", TIME_DISTRIBUTION_TASK, 3, -1);
    }
  }
  return true;
}

bool Historylogic::OnTimeout(struct server *srv, char *id, int opcode,
                             int time) {
  switch (opcode) {
    case TIME_DISTRIBUTION_TASK: {
      history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryTradesData();
      history_logic::HistoryEngine::GetSchdulerManager()
          ->InitHistoryRechargeData();
      history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryWithDrawals();
      break;
    }
    default:
      break;
  }
  return true;
}

bool Historylogic::OnHistoryTrades(struct server* srv, int socket,
                                   struct PacketHead *packet) {
  history_logic::net_request::HistoryPosition history_position;
  if (packet->packet_length <= PACKET_HEAD_LENGTH) {
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  bool r = history_position.set_http_packet(packet_control->body_);
  if (!r) {
    LOG_DEBUG2("packet_length %d",packet->packet_length);
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  history_logic::HistoryEngine::GetSchdulerManager()->SendHistoryTrades(
      socket, packet->session_id, packet->reserved, history_position.id(), history_position.symbol(),
      history_position.start(), history_position.count());
  return true;
}

bool Historylogic::OnHistoryRecharge(struct server* srv, int socket,
                                     struct PacketHead *packet) {
  history_logic::net_request::HistoryRecharge history_recharge;
  if (packet->packet_length <= PACKET_HEAD_LENGTH) {
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  bool r = history_recharge.set_http_packet(packet_control->body_);
  if (!r) {
    LOG_DEBUG2("packet_length %d",packet->packet_length);
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  history_logic::HistoryEngine::GetSchdulerManager()->SendHistoryRecharge(
      socket, packet->session_id, packet->reserved, history_recharge.id(),
      history_recharge.status(), history_recharge.start(),
      history_recharge.count());
  return true;
}

bool Historylogic::OnHistoryWithdrawals(struct server* srv, int socket,
                                        struct PacketHead * packet) {
  history_logic::net_request::HistoryWithDrawals history_withdrawals;
  if (packet->packet_length <= PACKET_HEAD_LENGTH) {
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  bool r = history_withdrawals.set_http_packet(packet_control->body_);
  if (!r) {
    LOG_DEBUG2("packet_length %d",packet->packet_length);
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }

  history_logic::HistoryEngine::GetSchdulerManager()->SendHistoryWithDrawls(
      socket, packet->session_id, packet->reserved, history_withdrawals.id(),
      history_withdrawals.status(), history_withdrawals.start(),
      history_withdrawals.count());
  return true;
}

bool Historylogic::OnHistoryTradesHandle(struct server* srv, int socket,
                                         struct PacketHead * packet) {
  history_logic::net_request::HistoryHandle history_handle;
  if (packet->packet_length <= PACKET_HEAD_LENGTH) {
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  bool r = history_handle.set_http_packet(packet_control->body_);
  if (!r) {
    LOG_DEBUG2("packet_length %d",packet->packet_length);
    send_error(socket, ERROR_TYPE, FORMAT_ERRNO, packet->session_id);
    return false;
  }

  history_logic::HistoryEngine::GetSchdulerManager()->HandleHistoryTrade(
      socket, packet->session_id, packet->reserved, history_handle.id(),
      history_handle.tid(), history_handle.handle());

  return true;
}

}  // namespace trades_logic
