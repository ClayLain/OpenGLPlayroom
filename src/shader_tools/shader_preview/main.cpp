#include "shader_preview_ui.h"

#include <error_handling/error_handling_utils.h>

enum class ResultCode
{
    Ok,
    UnhandledUserError,
    UnknownError
};

int main(int argc, char *argv[])
{
    try {
        shader_preview::startPreviewUi(argc, argv);
        return static_cast<int>(ResultCode::Ok);
    } catch (const error_handling::FatalErrorHandlerCalled &e) {
        return static_cast<int>(ResultCode::UnhandledUserError);
    } catch (const std::exception &e) {
        return static_cast<int>(ResultCode::UnknownError);
    }
}
