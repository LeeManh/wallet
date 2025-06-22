#include "exceptions/Exception.hpp"

#include "enums/Enums.hpp"

namespace exceptions {

BaseException::BaseException(enums::ExceptionType type, const std::string& msg)
    : type(type), msg(msg) {}

enums::ExceptionType BaseException::getType() const { return type; }

const char* BaseException::what() const noexcept { return msg.c_str(); }

AuthException::AuthException(const std::string& msg)
    : BaseException(enums::ExceptionType::AUTH_ERROR, msg) {}

ValidationException::ValidationException(const std::string& msg)
    : BaseException(enums::ExceptionType::VALIDATION_ERROR, msg) {}

NotFoundException::NotFoundException(const std::string& msg)
    : BaseException(enums::ExceptionType::NOT_FOUND_ERROR, msg) {}

StorageException::StorageException(const std::string& msg)
    : BaseException(enums::ExceptionType::STORAGE_ERROR, msg) {}

}  // namespace exceptions