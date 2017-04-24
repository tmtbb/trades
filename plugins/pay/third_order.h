//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#ifndef PUB_PAY_THIRD_ORDER_H_
#define PUB_PAY_THIRD_ORDER_H_

#include <string>
#include "logic/base_values.h"


const std::string T_APPID = "th9dc39aec13ee3158";
const std::string T_MCH_ID = "MNYH54001EBOM"; //商户号

//const std::string T_MPID = "the9f0932fb23e8f8a";

const std::string T_APP_KEY = "2017042116284843001"; //证书编号

const std::string T_APP_TRADE_TYPE = "APP";

const std::string THIRD_URL = "https://gw.uqiantu.net/native/";
const std::string THIRD_CASH_URL = "https://gw.uqiantu.net/native/";
const std::string THIRD_PACKAGE = "Sign=ThirdPay";
const std::string T_NOTIFY_URL =
    "http://139.224.34.22/cgi-bin/flight/pay/v1/third_callback.fcgi";
const std::string T_CASH_NOTIFY_URL =
    "http://139.224.34.22/cgi-bin/flight/pay/v1/third_cash_callback.fcgi";

/*
 */
namespace pay_logic {

class ThirdOrder {
 public:
  ThirdOrder();
  virtual ~ThirdOrder();

  inline void set_body(std::string b) {
    body = b;
  }
  inline void set_rec_bank_name(const std::string &value) {
    rec_bank_name = value;
  }
  inline void set_rec_branch_bank_name(const std::string &value) {
    rec_branch_bank_name = value;
  }
  inline void set_rec_card_no(const std::string &value) {
    rec_card_no = value;
  }
  inline void set_rec_account_name(const std::string &value) {
    rec_account_name = value;
  }
  inline void set_out_trade_no(std::string oid) {
    out_trade_no = oid;
  }
  inline void set_total_fee(int fee) {
    total_fee = fee;
  }
  inline void set_spbill_create_ip(std::string ip) {
    spbill_create_ip = ip;
  }
  inline void set_payment_info(const std::string &paymentinfo) {
    payment_info = paymentinfo;
  }
  inline void set_prepayid(std::string preid) {
    prepayid = preid;
  }
  void PreSign();
  void PreSerialize(base_logic::DictionaryValue* dic);
  std::string PlaceOrder();
  std::string PlaceOrder(const std::string& id, const std::string& pay_type,const std::string &content);
  std::string CashPlaceOrder(const std::string& id);

  inline std::string get_appid() {
    return appid;
  }
  inline std::string get_partnerid() {
    return mch_id;
  }
  inline std::string get_payment_info() {
    return payment_info;
  }
  inline std::string get_prepayid() {
    return prepayid;
  }
  inline std::string get_package() {
    return package;
  }
  inline std::string get_nonce_str() {
    return nonce_str;
  }
  inline std::string get_timestamp() {
    return timestamp;
  }
  inline std::string get_prepaysign() {
    return prepaysign;
  }

 private:
//拼接post下单参数
//"<xml>"
//    "<appid>wx9dc39aec13ee3158</appid>"
//    "<body>APP支付测试</body>"
//    "<mch_id>1404391902</mch_id>"
//    "<nonce_str>1add1a30ac87aa2db72f57a2375d8fec</nonce_str>"
//    "<prepay_id><![CDATA[wx20161031151837c7a7ea649a0616081781]]></prepay_id>"
//    "<notify_url>http://wxpay.weixin.qq.com/pub_v2/pay/notify.v2.php</notify_url>"
//    "<out_trade_no>1415659990</out_trade_no>"
//    "<spbill_create_ip>14.23.150.211</spbill_create_ip>"
//    "<total_fee>1</total_fee>"
//    "<trade_type>APP</trade_type>"
//    "<sign>2EAD4CA62CA2677D0C307CDDF6D6BC89</sign>"
//"</xml>";
  std::string PostFiled(bool iscash=false);
  void InitWxVerify();
  void InitWxVerify(const std::string& id);
  void InitWxVerify(const std::string& id, 
                    const std::string& pay_type,
                    const std::string& content);

//  微信下单签名
//  签名算法
//  签名生成的通用步骤如下：
//  第一步，设所有发送或者接收到的数据为集合M，将集合M内非空参数值的参数按照参数名ASCII码从小到大排序（字典序），使用URL键值对的格式（即key1=value1&key2=value2…）拼接成字符串stringA。
//  特别注意以下重要规则：
//  ◆ 参数名ASCII码从小到大排序（字典序）；
//  ◆ 如果参数的值为空不参与签名；
//  ◆ 参数名区分大小写；
//  ◆ 验证调用返回或微信主动通知签名时，传送的sign参数不参与签名，将生成的签名与该sign值作校验。
//  ◆ 微信接口可能增加字段，验证签名时必须支持增加的扩展字段
//  第二步，在stringA最后拼接上key得到stringSignTemp字符串，并对stringSignTemp进行MD5运算，再将得到的字符串所有字符转换为大写，得到sign值signValue。
//  key设置路径：微信商户平台(pay.weixin.qq.com)-->账户设置-->API安全-->密钥设置
//  举例：
//  假设传送的参数如下：
//  appid：  wxd930ea5d5a258f4f
//  mch_id： 10000100
//  device_info：  1000
//  body： test
//  nonce_str：  ibuaiVcKdpRxkhJA
//  第一步：对参数按照key=value的格式，并按照参数名ASCII字典序排序如下：
//  stringA="appid=wxd930ea5d5a258f4f&body=test&device_info=1000&mch_id=10000100&nonce_str=ibuaiVcKdpRxkhJA";
//  第二步：拼接API密钥：
//
//  stringSignTemp="stringA&key=192006250b4c09247ec02edce69f6a2d"
//  sign=MD5(stringSignTemp).toUpperCase()="9A0A8659F005D6984697E2CA0A9CF3B7"
  void PlaceOrderSign(bool iscash = false);
  //void PlaceOrderSign(const std::string& id, const std::string& m_id, const std::string& t_type,const std::string& k_key,
    //                  const int32 ptype,const std::string& open_id);
 private:
  //APP——需传入应用市场上的APP名字-实际商品名称，天天爱消除-游戏充值
  std::string body;
  //随机字符串，不长于32位
  std::string nonce_str;
  //用户端实际ip
  std::string spbill_create_ip;
  //支付类型 固定 为 APP //类型 0 app  1.微信公众号
  std::string trade_type;
  //商户key 参与sign签名-不做其他用途
  std::string key;

  //下单成功

  //微信生成的预支付回话标识，用于后续接口调用中使用，该值有效期为2小时
  std::string prepayid;
  //用于客户端调支付
  std::string prepaysign;
  //APP写固定值Sign=WXPay MP写prepay_id=微信订单id
  std::string package;
  //时间戳
  std::string timestamp;
//充值----------------------------------------------------------------------------------------------------------------
  //商户系统内部的订单号,32个字符内、可包含字母
  std::string out_trade_no;
  
  int total_fee;	//订单总金额，单位为分
  
  std::string mch_id; //merchantNo//支付分配的商户号
  //平台审核通过的应用APPID
  std::string appid;

  //签名，详见函数说明
  std::string sign;
  //接收支付异步通知回调地址，通知url必须为直接可访问的url，不能携带参数。
  std::string notify_url;
  std::string pay_type;		//支付类型
  std::string content;		//交易描述
  std::string payment_info;
//提现----------------------------------------------------------------------------------------------------------------
//
  std::string rec_bank_name;
  std::string rec_branch_bank_name;
  std::string rec_card_no;
  std::string rec_account_name;
//ret
//
  int transfer_amount; //实际到账金额
  int fee; //代收手续费
  std::string pay_no;
  std::string status;
};

}

#endif  // PUB_PAY_WXPAY_WX_ORDER_H_
