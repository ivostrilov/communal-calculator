#ifndef SOURCEFILES_VIEW_GUID_APPLICATION_H_
#define SOURCEFILES_VIEW_GUID_APPLICATION_H_

#include <QGuiApplication>
#include <memory>

#include "model_view/model_view.h"

namespace CommunalCalculator {

class GuidApplication : public QGuiApplication {
 public:
  GuidApplication() = delete;
  GuidApplication(const GuidApplication &) = delete;
  GuidApplication(GuidApplication &&) = delete;

  explicit GuidApplication(int &argc, char **argv,
                           const std::shared_ptr<ModelView> &model_view);

  auto operator=(const GuidApplication &) -> GuidApplication & = delete;
  auto operator=(GuidApplication &&) -> GuidApplication & = delete;

  ~GuidApplication() override = default;

  virtual auto Start(const char *qml_main_path) -> int;

 private:
  std::shared_ptr<ModelView> modelView_;
};

}  // namespace CommunalCalculator

#endif  // SOURCEFILES_VIEW_GUID_APPLICATION_H_
