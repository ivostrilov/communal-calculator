#include "view/guid_application.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace CommunalCalculator {

GuidApplication::GuidApplication(int &argc, char **argv,
                                 const std::shared_ptr<ModelView> &model_view)
    : QGuiApplication(argc, argv), modelView_(model_view) {}

auto GuidApplication::Start(const char *qml_main_path) -> int {
  QQmlApplicationEngine engine;

  auto *root_context = engine.rootContext();
  root_context->setContextProperty("modelView", modelView_.get());

  engine.load(QUrl(qml_main_path));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return QGuiApplication::exec();
}

}  // namespace CommunalCalculator
