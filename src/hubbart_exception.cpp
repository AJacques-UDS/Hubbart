#include "hubbart_exception.hpp"
#include "spdlog/spdlog.h"

HubbartException::HubbartException(const std::string &ent, const std::string &msg) {
    this->entity = ent;
    this->message = msg;
    spdlog::warn("{} Exception Occured: {}", this->entity, this->message);
}

std::string HubbartException::getMessage(void) {
    return this->message;
}

std::string HubbartException::getEntity(void) {
    return this->entity;
}