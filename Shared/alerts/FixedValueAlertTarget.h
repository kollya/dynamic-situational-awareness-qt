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

#ifndef FIXEDVALUEALERTTARGET_H
#define FIXEDVALUEALERTTARGET_H

#include <QVariant>

#include "AlertTarget.h"

class FixedValueAlertTarget : public AlertTarget
{
  Q_OBJECT

public:
  explicit FixedValueAlertTarget(const QVariant& value, QObject* parent = nullptr);
  ~FixedValueAlertTarget();

  virtual QList<Esri::ArcGISRuntime::Geometry> targetGeometries(const Esri::ArcGISRuntime::Envelope& targetArea) const override;
  QVariant targetValue() const override;

private:
  QVariant m_value;
};

#endif // FIXEDVALUEALERTTARGET_H