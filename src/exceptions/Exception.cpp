#include "exceptions/Exception.hpp"

namespace exceptions {

BaseException::BaseException(ExceptionType type, const std::string& msg)
    : type(type), msg(msg) {}

const char* BaseException::what() const noexcept { return msg.c_str(); }

ExceptionType BaseException::getType() const { return type; }

AuthException::AuthException(const std::string& msg)
    : BaseException(ExceptionType::AUTH_ERROR, msg) {}

ValidationException::ValidationException(const std::string& msg)
    : BaseException(ExceptionType::VALIDATION_ERROR, msg) {}

NotFoundException::NotFoundException(const std::string& msg)
    : BaseException(ExceptionType::NOT_FOUND_ERROR, msg) {}

StorageException::StorageException(const std::string& msg)
    : BaseException(ExceptionType::STORAGE_ERROR, msg) {}

}  // namespace exceptions