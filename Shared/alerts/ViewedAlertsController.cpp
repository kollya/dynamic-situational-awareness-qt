// Copyright 2017 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "AlertConditionData.h"
#include "AlertListModel.h"
#include "ViewedAlertsController.h"

#include "ToolManager.h"

using namespace Esri::ArcGISRuntime;

/*!
  \class ViewedAlertsController
  \inherits Toolkit::AbstractTool
  \brief Tool controller for managing the count of unviewed, active alert condition data.

  Alerts are created when a given \l AlertCondition is met.

  This tool reports changes to the total number of alert condition data which are
  active but have not been marked as viwed.

  \sa AlertListModel
  \sa AlertConditionData
 */

/*!
  \brief Constructor taking an optional \a parent.
 */
ViewedAlertsController::ViewedAlertsController(QObject* parent /* = nullptr */):
  Toolkit::AbstractTool(parent)
{
  Toolkit::ToolManager::instance().addTool(this);

  AlertListModel* model = AlertListModel::instance();
  if (model)
  {
    connect(model, &AlertListModel::dataChanged, this, &ViewedAlertsController::unviewedCountChanged);
    connect(model, &AlertListModel::rowsInserted, this, &ViewedAlertsController::unviewedCountChanged);
    connect(model, &AlertListModel::rowsRemoved, this, &ViewedAlertsController::unviewedCountChanged);
    emit unviewedCountChanged();
  }
}

/*!
  \brief The name of this tool.
 */
QString ViewedAlertsController::toolName() const
{
  return QString("viewed alerts");
}

/*!
  \brief Destructor.
 */
ViewedAlertsController::~ViewedAlertsController()
{
}

/*!
  \brief Returns the number of alert condition data objects which are currently active
  and which have not been marked as viewed.
 */
int ViewedAlertsController::unviewedCount() const
{
  AlertListModel* model = AlertListModel::instance();
  if (!model)
    return 0;

  int count = 0;
  const int alertsCount = model->rowCount();
  for (int i = 0; i < alertsCount; ++i)
  {
    AlertConditionData* alert = model->alertAt(i);
    if (!alert)
      continue;

    if (!alert->active())
      continue;

    if (alert->viewed())
      continue;

    count++;
  }

  return count;
}