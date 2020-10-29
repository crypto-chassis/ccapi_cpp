#ifndef INCLUDE_CCAPI_CPP_CCAPI_SUBSCRIPTION_H_
#define INCLUDE_CCAPI_CPP_CCAPI_SUBSCRIPTION_H_
#include "ccapi_cpp/ccapi_macro.h"
#include <string>
#include <set>
#include "ccapi_cpp/ccapi_util.h"
namespace ccapi {
class Subscription final {
 public:
  Subscription(std::string exchange, std::string instrument, std::string fields, std::string options = "", std::string correlationId =
                   UtilString::generateRandomString(CCAPI_CORRELATION_ID_GENERATED_LENGTH))
      : exchange(exchange), instrument(instrument), correlationId(correlationId) {
    std::vector<std::string> fieldList = UtilString::split(fields, ",");
    this->fieldSet = std::set<std::string>(fieldList.begin(), fieldList.end());
    std::vector<std::string> optionList;
    if (!options.empty()) {
      optionList = UtilString::split(options, "&");
    }
    this->optionMap[CCAPI_EXCHANGE_NAME_MARKET_DEPTH_MAX] =
    CCAPI_EXCHANGE_VALUE_MARKET_DEPTH_MAX_DEFAULT;
    this->optionMap[CCAPI_EXCHANGE_NAME_CONFLATE_INTERVAL_MILLISECONDS] =
    CCAPI_EXCHANGE_VALUE_CONFLATE_INTERVAL_MILLISECONDS_DEFAULT;
    this->optionMap[CCAPI_EXCHANGE_NAME_CONFLATE_GRACE_PERIOD_MILLISECONDS] =
    CCAPI_EXCHANGE_VALUE_CONFLATE_GRACE_PERIOD_MILLISECONDS_DEFAULT;
    for (const auto & option : optionList) {
      auto optionKeyValue = UtilString::split(option, "=");
      this->optionMap[optionKeyValue.at(0)] = optionKeyValue.at(1);
    }
    this->serviceName = CCAPI_EXCHANGE_NAME_MARKET_DATA;
  }
  Subscription(std::map<std::string, std::string> credential, std::string exchange, std::string instrument = "", std::string correlationId =
      UtilString::generateRandomString(CCAPI_CORRELATION_ID_GENERATED_LENGTH)): credential(credential), exchange(exchange), instrument(instrument), correlationId(correlationId) {
    this->serviceName = CCAPI_EXCHANGE_NAME_EXECUTION_MANAGEMENT;
  }
  std::string toString() const {
    std::string output = "Subscription [exchange = " + exchange + ", instrument = " + instrument + ", fieldSet = "
        + ccapi::toString(fieldSet) + ", optionMap = " + ccapi::toString(optionMap) + ", correlationId = "
        + correlationId + ", credential = "
        + ccapi::toString(credential) + ", serviceName = " + serviceName + "]";
    return output;
  }
  const std::string& getCorrelationId() const {
    return correlationId;
  }
  const std::string& getExchange() const {
    return exchange;
  }
  const std::string& getInstrument() const {
    return instrument;
  }
  const std::set<std::string>& getFieldSet() const {
    return fieldSet;
  }
  const std::map<std::string, std::string>& getOptionMap() const {
    return optionMap;
  }
  const std::map<std::string, std::string>& getCredential() const {
    return credential;
  }
  const std::string& getServiceName() const {
    return serviceName;
  }

 private:
  std::string exchange;
  std::string instrument;
  std::set<std::string> fieldSet;
  std::map<std::string, std::string> optionMap;
  std::string correlationId;
  std::map<std::string, std::string> credential;
  std::string serviceName;
};
} /* namespace ccapi */
#endif  // INCLUDE_CCAPI_CPP_CCAPI_SUBSCRIPTION_H_