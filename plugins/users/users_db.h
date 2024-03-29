//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef SWP_USERS_DB_H_
#define SWP_USERS_DB_H_

#include <string>
#include <list>
#include "storage/data_engine.h"
#include "logic/swp_infos.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "users/users_proto_buf.h"

namespace users_logic {

class UsersDB {
 public:
  UsersDB(config::FileConfig* config);
  ~UsersDB();

 public:
  bool RegisterAccount(const std::string& phone_num, const std::string& passwd,
                       const int32 type,int64& uid, int32& result, const std::string &agentid, const std::string &recommend, 
		       const std::string &device_id, const int64 member_id);

  bool WXBindAccount(const std::string& phone_num, const std::string& passwd,
                       const int32 type,int64& uid, int32& result, const std::string &openid, const std::string &nick_name, 
		       const std::string &head_url, const std::string &agent_id, const std::string &recommend,
		       const std::string &device_id, const int64 member_id);

  bool LoginAccount(const std::string& phone_num, const std::string& passwd, const std::string& device_id,
                    const std::string& ip, swp_logic::UserInfo& user);
  bool LoginWiXin(const std::string& open_id, const std::string& device_id,
                    const std::string& ip, swp_logic::UserInfo& user, std::string &passwd);

  bool CheckAccountExist(const std::string& phone);

  bool AccountBalance(const int64 uid, double & balance);

  bool ModifyPwd(const std::string &phone, const std::string &newpwd);

  bool GetVersion(const int32 type, users_logic::net_reply::TGetVersion &get_version);

  bool GetUserInfo(const int64 uid, const std::string& ip,
                   swp_logic::UserInfo& userinfo);

 public:
  static void CallRegisterAccount(void* param, base_logic::Value* value);

  static void CallGetVersion(void* param, base_logic::Value* value);

  static void CallLoginAccount(void* param, base_logic::Value* value);

  static void CallAccountBalance(void* param, base_logic::Value* value);

  static void CallCheckAccountExist(void* param, base_logic::Value* value);
 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace history_logic

#endif /* SWP_HISTORY_DB_H_ */
