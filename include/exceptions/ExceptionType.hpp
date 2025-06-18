#pragma once

namespace exceptions {

enum class ExceptionType {
  AUTH_ERROR,
  VALIDATION_ERROR,
  NOT_FOUND_ERROR,
  STORAGE_ERROR,
  UNKNOWN_ERROR
};

}