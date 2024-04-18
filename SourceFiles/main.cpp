#include <QStandardPaths>

#include "view/guid_application.h"

// TODO(i.vostrilov): russian language

inline constexpr char const *kMainQmlPath = "qrc:/qml/Main.qml";

auto main(int argc, char *argv[]) -> int {
  auto app_data_path =
      QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
          .toStdString();

  auto model = std::make_shared<CommunalCalculator::Core::Model>();
  model->Initialize(app_data_path);

  auto model_view = std::make_shared<CommunalCalculator::ModelView>();
  model_view->ConnectModel(model);

  CommunalCalculator::GuidApplication application(argc, argv, model_view);
  return application.Start(kMainQmlPath);
}
