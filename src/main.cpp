#include "config/app_config.hpp"

#include <crow.h>
#include <spdlog/spdlog.h>

#include <exception>

int main() {
  try {
    const AppConfig config = AppConfig::from_environment();

    crow::SimpleApp app;

    CROW_ROUTE(app, "/health")([] {
      crow::json::wvalue response;

      response["status"] = "ok";
      response["service"] = "cpp-auth-service";

      return response;
    });

    spdlog::info("Starting C++ Auth Service on port {}", config.server_port);

    app.port(config.server_port).multithreaded().run();

    return 0;
  } catch (const std::exception &exception) {
    spdlog::critical("Application startup failed: {}", exception.what());

    return 1;
  }
}