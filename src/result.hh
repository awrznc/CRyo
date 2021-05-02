namespace cryo {

/**
  * Result is a class that represents either success or failure.
  *
  * example:
  *
  * ```cc
  * #include <iostream>
  * #include "result.hh"
  *
  * int main() {
  *     cryo::Result<int, std::string> value(0, std::string(""));
  *     value.setError(std::string("Runtime error."));
  *
  *     if ( value.is_error() ) {
  *         std::cout << value.Error() << std::endl;
  *     }
  *     return 0;
  * }
  * ```
  **/
template <typename OK, typename ERROR> class Result {
private:
    enum {
        OK_STATUS,
        ERROR_STATUS,
        UNSETTLED_STATUS
    } typedef Status;
    Status status;

public:
    /**
      * Initialize Result instance.
      *
      * ```cc
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value;
      *     return 0;
      * }
      * ```
      **/
    Result() {
        this->status = Status::UNSETTLED_STATUS;
    }

    /**
      * Initialize Result instance with default value.
      *
      * ```cc
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     return 0;
      * }
      * ```
      **/
    Result(OK ok_value, ERROR error_value) {
        this->ok_value = ok_value;
        this->error_value = error_value;
        this->status = Status::UNSETTLED_STATUS;
    }

    /**
      * Set the OK value and status.
      *
      * ```cc
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     value.setOk(1);
      *     return 0;
      * }
      * ```
      **/
    OK setOk(OK value) {
        this->status = Status::OK_STATUS;
        this->ok_value = value;
    }

    /**
      * Set the OK value and status.
      *
      * ```cc
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     value.setError(std::string("sample"));
      *     return 0;
      * }
      * ```
      **/
    ERROR setError(ERROR value) {
        this->status = Status::ERROR_STATUS;
        this->error_value = value;
    }

    /**
      * Returns true if the result is Ok.
      *
      * ```cc
      * #include <assert.h>
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     value.setOk(0);
      *     assert(value.is_ok() == true);
      *     return 0;
      * }
      * ```
      **/
    bool is_ok() {
        return this->status == Status::OK_STATUS;
    }

    /**
      * Returns true if the result is Error.
      *
      * ```cc
      * #include <assert.h>
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     value.setError(std::string("error"));
      *     assert(value.is_error() == true);
      *     return 0;
      * }
      * ```
      **/
    bool is_error() {
        return this->status == Status::ERROR_STATUS;
    }

    /**
      * Returns true if the result is Unsettled.
      *
      * ```cc
      * #include <assert.h>
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string(""));
      *     assert(value.is_unsettled() == true);
      *     return 0;
      * }
      * ```
      **/
    bool is_unsettled() {
        return this->status == Status::UNSETTLED_STATUS;
    }

    /**
      * Get the OK value.
      *
      * ```cc
      * #include <assert.h>
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(1, std::string(""));
      *     assert(value.Ok() == 1);
      *     return 0;
      * }
      * ```
      **/
    OK Ok() {
        return this->ok_value;
    }

    /**
      * Get the Error value.
      *
      * ```cc
      * #include <assert.h>
      * #include <string>
      * #include "result.hh"
      *
      * int main() {
      *     cryo::Result<int, std::string> value(0, std::string("sample"));
      *     assert(value.Error() == std::string("sample"));
      *     return 0;
      * }
      * ```
      **/
    ERROR Error() {
        return this->error_value;
    }

    OK ok_value;
    ERROR error_value;
};

}
