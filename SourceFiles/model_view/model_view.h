#ifndef SOURCEFILES_MODEL_VIEW_MODEL_VIEW_H_
#define SOURCEFILES_MODEL_VIEW_MODEL_VIEW_H_

#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <memory>

#include "core/communal_counter.h"
#include "core/model.h"

namespace CommunalCalculator {

class ModelView : public QObject,
                  public std::enable_shared_from_this<ModelView> {
  Q_OBJECT

 public:
  ModelView() = default;
  ModelView(const ModelView &) = delete;
  ModelView(ModelView &&) = delete;

  auto operator=(const ModelView &) -> ModelView & = delete;
  auto operator=(ModelView &&) -> ModelView & = delete;

  ~ModelView() override = default;

  void ConnectModel(const std::shared_ptr<Core::Model> &model_view);

 signals:
  void summaryCalculated(const QMap<QString, QVariant> &result);
  void appCfgChanged(const QMap<QString, QVariant> &cfg);

 public slots:
  auto onGetAppConfiguration() -> QMap<QString, QVariant>;

  virtual void onCalculateSummary(const QMap<QString, QVariant> &values);
  virtual void onAppCfgChanged(const QMap<QString, QVariant> &values);

 private:
  static auto CreatCommunalCounter(Core::CommunalCounter::Type type)
      -> std::shared_ptr<Core::CommunalCounter>;

  // Because in lambda can't use 'emit'
  void EmitSummaryCalculated(const QMap<QString, QVariant> &result);
  void EmitAppCfgChanged(const QMap<QString, QVariant> &cfg);

  std::shared_ptr<Core::Model> model_;
};

}  // namespace CommunalCalculator

#endif  // SOURCEFILES_MODEL_VIEW_MODEL_VIEW_H_
