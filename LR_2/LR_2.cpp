#include <iostream>
#include <float.h>
#include <Windows.h>

int main() {
    SetErrorMode(SEM_NOGPFAULTERRORBOX);

    double num1, num2, result;

    std::cout << "Enter two numbers (second should be large): ";
    std::cin >> num1 >> num2;

    __try {
        result = num1 / num2;

        if (result == 0) {
            RaiseException(EXCEPTION_FLT_UNDERFLOW, 0, 0, NULL);
        }

        std::cout << "Result: " << result << std::endl;
    }
    __except (GetExceptionCode() == EXCEPTION_FLT_UNDERFLOW ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        std::cout << "Floating point underflow exception caught." << std::endl;
    }

    return 0;
}
