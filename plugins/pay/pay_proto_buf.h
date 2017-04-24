//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#ifndef SWP_PAY_PAY_PROTO_BUF_
#define SWP_PAY_PAY_PROTO_BUF_

#include "basic/basic_util.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include <list>
#include <string>

namespace pay_logic {

namespace net_request {

class WXPayServer {
 public:
  WXPayServer()
      : appid_(NULL),
        mch_id_(NULL),
        total_fee_(NULL),
        recharge_id_(NULL),
        pay_result_(NULL),
        transaction_id_(NULL),
        time_end_(NULL) {
  }

  ~WXPayServer() {
    if (appid_) {
      delete appid_;
      appid_ = NULL;
    }
    if (mch_id_) {
      delete mch_id_;
      mch_id_ = NULL;
    }
    if (total_fee_) {
      delete total_fee_;
      total_fee_ = NULL;
    }
    if (recharge_id_) {
      delete recharge_id_;
      recharge_id_ = NULL;
    }
    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
    if (transaction_id_) {
      delete transaction_id_;
      transaction_id_ = NULL;
    }
    if (time_end_) {
      delete time_end_;
      time_end_ = NULL;
    }
  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_appid(std::string appid) {
    appid_ = new base_logic::StringValue(appid);
  }

  void set_mch_id(std::string mch_id) {
    mch_id_ = new base_logic::StringValue(mch_id);
  }

  void set_total_fee(int64 total_fee) {
    total_fee_ = new base_logic::FundamentalValue(total_fee);
  }

  void set_recharge_id(int64 recharge_id) {
    recharge_id_ = new base_logic::FundamentalValue(recharge_id);
  }

  void set_pay_result(int64 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  void set_transaction_id(std::string transaction_id) {
    transaction_id_ = new base_logic::StringValue(transaction_id);
  }

  void set_time_end(std::string& time_end) {
    time_end_ = new base_logic::StringValue(time_end);
  }

  std::string appid() {
    std::string appid;
    if (appid_)
      appid_->GetAsString(&appid);
    return appid;
  }

  std::string mch_id() {
    std::string mch_id;
    if (mch_id_)
      mch_id_->GetAsString(&mch_id);
    return mch_id;
  }

  std::string transaction_id() const {
    std::string transaction_id;
    if (transaction_id_)
      transaction_id_->GetAsString(&transaction_id);
    return transaction_id;
  }

  int64 total_fee() {
    int64 total_fee;
    if (total_fee_)
      total_fee_->GetAsBigInteger(&total_fee);
    return total_fee;
  }

  int64 recharge_id() {
    int64 recharge_id;
    if (recharge_id_)
      recharge_id_->GetAsBigInteger(&recharge_id);
    return recharge_id;
  }

  int64 pay_result() {
    int64 pay_result;
    if (pay_result_)
      pay_result_->GetAsBigInteger(&pay_result);
    return pay_result;
  }

 private:
  base_logic::StringValue* appid_;
  base_logic::StringValue* mch_id_;
  base_logic::FundamentalValue* total_fee_;
  base_logic::FundamentalValue* recharge_id_;
  base_logic::FundamentalValue* pay_result_;  //1 - 支付成功
  base_logic::StringValue* transaction_id_;
  base_logic::StringValue* time_end_;
};

class WXPayClient {
 public:
  WXPayClient()
      : uid_(NULL),
        rid_(NULL),
        pay_result_(NULL) {
  }

  ~WXPayClient() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }

    if (rid_) {
      delete rid_;
      rid_ = NULL;
    }

    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(const int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_rid(const int64 rid) {
    rid_ = new base_logic::FundamentalValue(rid);
  }

  void set_pay_result(const int32 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  const int32 uid() const {
    int64 uid = 0;
    uid_->GetAsBigInteger(&uid);
    return uid;
  }

  const int64 rid() const {
    int64 rid = 0;
    rid_->GetAsBigInteger(&rid);
    return rid;
  }

  const int32 pay_result() const {
    int32 pay_result = 0;
    pay_result_->GetAsInteger(&pay_result);
    return pay_result;
  }

 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* rid_;
  base_logic::FundamentalValue* pay_result_;
};

class WXPayOrder {
 public:
  WXPayOrder()
      : uid_(NULL),
        title_(NULL),
        price_(NULL),
        pay_type_(NULL),
        open_id_(NULL){
  }

  ~WXPayOrder() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }
    if (title_) {
      delete title_;
      title_ = NULL;
    }
    if (price_) {
      delete price_;
      price_ = NULL;
    }

    if (pay_type_) {
      delete pay_type_;
      pay_type_ = NULL;
    }

    if (open_id_) {
      delete open_id_;
      open_id_ = NULL;
    }
  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_title(std::string& title) {
    title_ = new base_logic::StringValue(title);
  }

  void set_price(double price) {
    price_ = new base_logic::FundamentalValue(price);
  }

  void set_pay_type(int32 pay_type) {
    pay_type_ = new base_logic::FundamentalValue(pay_type);
  }

  void set_open_id(const std::string& open_id) {
    open_id_ = new base_logic::StringValue(open_id);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }

  std::string title() {
    std::string title;
    if (title_)
      title_->GetAsString(&title);
    return title;
  }

  double price() {
    double price;
    if (price_)
      price_->GetAsReal(&price);
    return price;
  }

  int32 pay_type() {
    int32 pay_type;
    pay_type_->GetAsInteger(&pay_type);
    return pay_type;
  }

  const std::string open_id() {
    std::string open_id;
    if (open_id_)
      open_id_->GetAsString(&open_id);
    return open_id;
  }

 private:
  base_logic::FundamentalValue* uid_;
  base_logic::StringValue* title_;  //应用名-商品名 eg.交易支付
  base_logic::FundamentalValue* price_;  // 订单总价  单位 分
  base_logic::FundamentalValue* pay_type_;  //1为微信APP 0 微信公众号
  base_logic::StringValue* open_id_;//微信公众号支付必填
};

//Third
class ThirdPayServer {
 public:
  ThirdPayServer()
      : appid_(NULL),
        mch_id_(NULL),
        total_fee_(NULL),
        recharge_id_(NULL),
        pay_result_(NULL),
        transaction_id_(NULL),
        time_end_(NULL) {
  }

  ~ThirdPayServer() {
    if (appid_) {
      delete appid_;
      appid_ = NULL;
    }
    if (mch_id_) {
      delete mch_id_;
      mch_id_ = NULL;
    }
    if (total_fee_) {
      delete total_fee_;
      total_fee_ = NULL;
    }
    if (recharge_id_) {
      delete recharge_id_;
      recharge_id_ = NULL;
    }
    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
    if (transaction_id_) {
      delete transaction_id_;
      transaction_id_ = NULL;
    }
    if (time_end_) {
      delete time_end_;
      time_end_ = NULL;
    }
  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_appid(std::string appid) {
    appid_ = new base_logic::StringValue(appid);
  }

  void set_mch_id(std::string mch_id) {
    mch_id_ = new base_logic::StringValue(mch_id);
  }

  void set_total_fee(int64 total_fee) {
    total_fee_ = new base_logic::FundamentalValue(total_fee);
  }

  void set_recharge_id(int64 recharge_id) {
    recharge_id_ = new base_logic::FundamentalValue(recharge_id);
  }

  void set_pay_result(int64 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  void set_transaction_id(std::string transaction_id) {
    transaction_id_ = new base_logic::StringValue(transaction_id);
  }

  void set_time_end(std::string& time_end) {
    time_end_ = new base_logic::StringValue(time_end);
  }

  std::string appid() {
    std::string appid;
    if (appid_)
      appid_->GetAsString(&appid);
    return appid;
  }

  std::string mch_id() {
    std::string mch_id;
    if (mch_id_)
      mch_id_->GetAsString(&mch_id);
    return mch_id;
  }

  std::string transaction_id() const {
    std::string transaction_id;
    if (transaction_id_)
      transaction_id_->GetAsString(&transaction_id);
    return transaction_id;
  }

  int64 total_fee() {
    int64 total_fee;
    if (total_fee_)
      total_fee_->GetAsBigInteger(&total_fee);
    return total_fee;
  }

  int64 recharge_id() {
    int64 recharge_id;
    if (recharge_id_)
      recharge_id_->GetAsBigInteger(&recharge_id);
    return recharge_id;
  }

  int64 pay_result() {
    int64 pay_result;
    if (pay_result_)
      pay_result_->GetAsBigInteger(&pay_result);
    return pay_result;
  }

 private:
  base_logic::StringValue* appid_;
  base_logic::StringValue* mch_id_;
  base_logic::FundamentalValue* total_fee_;
  base_logic::FundamentalValue* recharge_id_;
  base_logic::FundamentalValue* pay_result_;  //1 - 支付成功
  base_logic::StringValue* transaction_id_;
  base_logic::StringValue* time_end_;
};

class ThirdPayClient {
 public:
  ThirdPayClient()
      : uid_(NULL),
        rid_(NULL),
        pay_result_(NULL) {
  }

  ~ThirdPayClient() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }

    if (rid_) {
      delete rid_;
      rid_ = NULL;
    }

    if (pay_result_) {
      delete pay_result_;
      pay_result_ = NULL;
    }
  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(const int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_rid(const int64 rid) {
    rid_ = new base_logic::FundamentalValue(rid);
  }

  void set_pay_result(const int32 pay_result) {
    pay_result_ = new base_logic::FundamentalValue(pay_result);
  }

  const int32 uid() const {
    int64 uid = 0;
    uid_->GetAsBigInteger(&uid);
    return uid;
  }

  const int64 rid() const {
    int64 rid = 0;
    rid_->GetAsBigInteger(&rid);
    return rid;
  }

  const int32 pay_result() const {
    int32 pay_result = 0;
    pay_result_->GetAsInteger(&pay_result);
    return pay_result;
  }

 private:
  base_logic::FundamentalValue* uid_;
  base_logic::FundamentalValue* rid_;
  base_logic::FundamentalValue* pay_result_;
};

class ThirdPayOrder {
 public:
  ThirdPayOrder()
      : uid_(NULL),
	merchant_no_(NULL),
	amount_(NULL),
	out_trade_no_(NULL),
	currency_(NULL),
	content_(NULL),
	pay_type_(NULL)
	{
  }

  ~ThirdPayOrder() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }

    if (pay_type_) {
      delete pay_type_;
      pay_type_ = NULL;
    }

    if (merchant_no_) {
      delete merchant_no_;
      merchant_no_= NULL;
    }
    if (amount_) {
      delete amount_;
      amount_= NULL;
    }
    if (out_trade_no_) {
      delete out_trade_no_;
      out_trade_no_= NULL;
    }

    if (currency_) {
      delete currency_;
      currency_= NULL;
    }

    if (content_) {
      delete content_;
      content_= NULL;
    }

  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_merchant_no(std::string& merchant_no) {
    merchant_no_ = new base_logic::StringValue(merchant_no);
  }

  void set_amount(double amount) {
    amount_ = new base_logic::FundamentalValue(amount);
  }

  void set_pay_type(const std::string& pay_type) {
    pay_type_ = new base_logic::StringValue(pay_type);
  }
  void set_out_trade_no(const std::string& out_trade_no) {
    out_trade_no_ = new base_logic::StringValue(out_trade_no);
  }
  void set_currency(const std::string& currency) {
    currency_ = new base_logic::StringValue(currency);
  }
  void set_content(const std::string& content) {
    content_ = new base_logic::StringValue(content);
  }

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  const std::string merchant_no() {
    std::string merchant_no;
    if (merchant_no_)
      merchant_no_->GetAsString(&merchant_no);
    return merchant_no;
  }

  double amount() {
    double amount;
    if (amount_)
      amount_->GetAsReal(&amount);
    return amount;
  }

  const std::string pay_type() {
    std::string pay_type;
    if (pay_type_)
      pay_type_->GetAsString(&pay_type);
    return pay_type;
  }
  const std::string out_trade_no() {
    std::string out_trade_no;
    if (out_trade_no_)
      out_trade_no_->GetAsString(&out_trade_no);
    return out_trade_no;
  }
  const std::string currency() {
    std::string currency;
    if (currency_)
      currency_->GetAsString(&currency);
    return currency;
  }
  const std::string content() {
    std::string content;
    if (content_)
      content_->GetAsString(&content);
    return content;
  }

 private:
  base_logic::FundamentalValue* uid_;
 // base_logic::StringValue* title_;  //应用名-商品名 eg.交易支付
 // base_logic::FundamentalValue* price_;  // 订单总价  单位 分
 // base_logic::FundamentalValue* pay_type_;  //1为微信APP 0 微信公众号
 // base_logic::StringValue* open_id_;//微信公众号支付必填

  base_logic::StringValue* merchant_no_;//
  base_logic::FundamentalValue* amount_;  // 订单总价  单位 分
  base_logic::StringValue* out_trade_no_;//
  base_logic::StringValue* currency_;//
  base_logic::StringValue* content_;//
  base_logic::StringValue* pay_type_;//
};


class ThirdCashOrder {
 public:
  ThirdCashOrder()
      : uid_(NULL),
	rec_bank_name_(NULL),
	amount_(NULL),
	rec_branch_bank_name_(NULL),
	rec_card_no_(NULL),
//	content_(NULL),
	rec_account_name_(NULL)
	{
  }

  ~ThirdCashOrder() {
    if (uid_) {
      delete uid_;
      uid_ = NULL;
    }

    if (rec_account_name_) {
      delete rec_account_name_;
      rec_account_name_ = NULL;
    }

    if (rec_bank_name_) {
      delete rec_bank_name_;
      rec_bank_name_= NULL;
    }
    if (amount_) {
      delete amount_;
      amount_= NULL;
    }
    if (rec_branch_bank_name_) {
      delete rec_branch_bank_name_;
      rec_branch_bank_name_= NULL;
    }

    if (rec_card_no_) {
      delete rec_card_no_;
      rec_card_no_= NULL;
    }

    //if (content_) { delete content_; content_= NULL; }

  }

  bool set_http_packet(base_logic::DictionaryValue* value);

  void set_uid(int64 uid) {
    uid_ = new base_logic::FundamentalValue(uid);
  }

  void set_rec_bank_name(std::string& rec_bank_name) {
    rec_bank_name_ = new base_logic::StringValue(rec_bank_name);
  }

  void set_amount(double amount) {
    amount_ = new base_logic::FundamentalValue(amount);
  }

  void set_rec_account_name(const std::string& rec_account_name) {
    rec_account_name_ = new base_logic::StringValue(rec_account_name);
  }
  void set_rec_branch_bank_name(const std::string& rec_branch_bank_name) {
    rec_branch_bank_name_ = new base_logic::StringValue(rec_branch_bank_name);
  }
  void set_rec_card_no(const std::string& rec_card_no) {
    rec_card_no_ = new base_logic::StringValue(rec_card_no);
  }
 // void set_content(const std::string& content) {
   // content_ = new base_logic::StringValue(content);
  //}

  int64 uid() {
    int64 uid;
    if (uid_)
      uid_->GetAsBigInteger(&uid);
    return uid;
  }
  const std::string rec_bank_name() {
    std::string rec_bank_name;
    if (rec_bank_name_)
      rec_bank_name_->GetAsString(&rec_bank_name);
    return rec_bank_name;
  }

  double amount() {
    double amount;
    if (amount_)
      amount_->GetAsReal(&amount);
    return amount;
  }

  const std::string rec_account_name() {
    std::string rec_account_name;
    if (rec_account_name_)
      rec_account_name_->GetAsString(&rec_account_name);
    return rec_account_name;
  }
  const std::string rec_branch_bank_name() {
    std::string rec_branch_bank_name;
    if (rec_branch_bank_name_)
      rec_branch_bank_name_->GetAsString(&rec_branch_bank_name);
    return rec_branch_bank_name;
  }
  const std::string rec_card_no() {
    std::string rec_card_no;
    if (rec_card_no_)
      rec_card_no_->GetAsString(&rec_card_no);
    return rec_card_no;
  }
 /* const std::string content() {
    std::string content;
    if (content_)
      content_->GetAsString(&content);
    return content;
  }
*/

 private:
  base_logic::FundamentalValue* uid_;

//  base_logic::StringValue* content_;//

  base_logic::FundamentalValue* amount_;  // 订单总价  单位 分
  base_logic::StringValue* rec_bank_name_;//recivebankname
  base_logic::StringValue* rec_branch_bank_name_;//
  base_logic::StringValue* rec_card_no_;//
  base_logic::StringValue* rec_account_name_;//收款人开户名称
};

//end Third

}

namespace net_reply {

class WXPayOrder {
 public:
  WXPayOrder()
      : appid_(NULL),
        partnerid_(NULL),
        prepayid_(NULL),
        packetage_(NULL),
        noncestr_(NULL),
        timestamp_(NULL),
        sign_(NULL),
        rid_(NULL),
        value_(NULL) {
  }

  ~WXPayOrder() {
    if (value_) {
      delete value_;
      value_ = NULL;
    }
  }
  void set_appid(const std::string& appid) {
    appid_ = new base_logic::StringValue(appid);
  }

  void set_partnerid(const std::string& partnerid) {
    partnerid_ = new base_logic::StringValue(partnerid);
  }

  void set_prepayid(const std::string& prepayid) {
    prepayid_ = new base_logic::StringValue(prepayid);
  }

  void set_packetage(const std::string& packetage) {
    packetage_ = new base_logic::StringValue(packetage);
  }

  void set_noncestr(const std::string& noncestr) {
    noncestr_ = new base_logic::StringValue(noncestr);
  }

  void set_timestamp(const std::string& timestamp) {
    timestamp_ = new base_logic::StringValue(timestamp);
  }

  void set_sign(const std::string& sign) {
    sign_ = new base_logic::StringValue(sign);
  }

  void set_rid(const int64 rid) {
    std::string str_rid = base::BasicUtil::StringUtil::Int64ToString(rid);
    rid_ = new base_logic::StringValue(str_rid);
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (appid_ != NULL)
      value_->Set(L"appid", appid_);
    if (appid_ != NULL)
      value_->Set(L"partnerid", partnerid_);
    if (appid_ != NULL)
      value_->Set(L"prepayid", prepayid_);
    if (appid_ != NULL)
      value_->Set(L"package", packetage_);
    if (appid_ != NULL)
      value_->Set(L"noncestr", noncestr_);
    if (appid_ != NULL)
      value_->Set(L"timestamp", timestamp_);
    if (appid_ != NULL)
      value_->Set(L"sign", sign_);
    if (appid_ != NULL)
      value_->Set(L"rid", rid_);

    return value_;
  }

 private:
  base_logic::StringValue* appid_;
  base_logic::StringValue* partnerid_;
  base_logic::StringValue* prepayid_;
  base_logic::StringValue* packetage_;
  base_logic::StringValue* noncestr_;
  base_logic::StringValue* timestamp_;  //为兼容暂时使用string
  base_logic::StringValue* sign_;
  base_logic::StringValue* rid_;  //为兼容暂时使用string
  base_logic::DictionaryValue* value_;
};

class Balance {
 public:
  Balance()
      : balance_(NULL),
        value_(NULL) {
  }

  ~Balance() {
    if (value_ != NULL) {
      delete value_;
      value_ = NULL;
    }
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (balance_ != NULL)
      value_->Set("balance", balance_);
    return value_;
  }

  void set_balance(double balance) {
    balance_ = new base_logic::FundamentalValue(balance);
  }
 private:
  base_logic::FundamentalValue* balance_;
  base_logic::DictionaryValue* value_;
};


class ThirdPayOrder {
 public:
  ThirdPayOrder()
      : payment_info_(NULL) {
  }

  ~ThirdPayOrder() {
    if (payment_info_) {
      delete payment_info_;
      payment_info_= NULL;
    }
  }
  void set_payment_info(const std::string& payment_info) {
    payment_info_ = new base_logic::StringValue(payment_info);
  }


  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (payment_info_ != NULL)
      value_->Set(L"paymentInfo", payment_info_);

    return value_;
  }

 private:
  base_logic::StringValue* payment_info_;
  //base_logic::StringValue* rid_;  //为兼容暂时使用string
  base_logic::DictionaryValue* value_;
};



class ThirdCashOrder {
 public:
  ThirdCashOrder()
      : merchant_no_(NULL),
        out_pay_no_(NULL),
        amount_(NULL),
        transfer_amount_(NULL),
        fee_(NULL),
        pay_no_(NULL),
        status_(NULL)
      {
  }

  ~ThirdCashOrder() {
    if (merchant_no_) {
      delete merchant_no_;
      merchant_no_= NULL;
    }
    if (out_pay_no_) {
      delete out_pay_no_;
      out_pay_no_= NULL;
    }
    if (amount_) {
      delete amount_;
      amount_= NULL;
    }
    if (transfer_amount_) {
      delete transfer_amount_;
      transfer_amount_= NULL;
    }
    if (fee_) {
      delete fee_;
      fee_= NULL;
    }
    if (pay_no_) {
      delete pay_no_;
      pay_no_= NULL;
    }
    if (status_) {
      delete status_;
      status_= NULL;
    }
  }
  void set_merchant_no(const std::string& merchant_no) {
    merchant_no_ = new base_logic::StringValue(merchant_no);
  }

  void set_out_pay_no(const std::string& out_pay_no) {
    out_pay_no_ = new base_logic::StringValue(out_pay_no);
  }

  void set_amount(const std::string& amount) {
    amount_ = new base_logic::StringValue(amount);
  }
  void set_transfer_amount(const std::string& transfer_amount) {
    transfer_amount_ = new base_logic::StringValue(transfer_amount);
  }
  void set_fee(const std::string& fee) {
    fee_= new base_logic::StringValue(fee);
  }
  void set_pay_no(const std::string& pay_no) {
    pay_no_ = new base_logic::StringValue(pay_no);
  }
  void set_status(const std::string& status) {
    status_ = new base_logic::StringValue(status);
  }
  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (merchant_no_ != NULL)
      value_->Set(L"merchantNo", merchant_no_);

    if (out_pay_no_ != NULL)
      value_->Set(L"outPayNo", out_pay_no_);
    if (amount_ != NULL)
      value_->Set(L"amount", amount_ );
    if (transfer_amount_ != NULL)
      value_->Set(L"transferAmount", transfer_amount_ );
    if (fee_ != NULL)
      value_->Set(L"fee", fee_);
    if (pay_no_ != NULL)
      value_->Set(L"payNo", pay_no_);
    if (status_ != NULL)
      value_->Set(L"status", status_);
    return value_;
  }

 private:
  base_logic::StringValue* merchant_no_;
  base_logic::StringValue* out_pay_no_;
  base_logic::StringValue*  amount_;
  base_logic::StringValue* transfer_amount_;
  base_logic::StringValue* fee_;
  base_logic::StringValue* pay_no_;
  base_logic::StringValue* status_;

  base_logic::DictionaryValue* value_;
};

}

}
#endif
