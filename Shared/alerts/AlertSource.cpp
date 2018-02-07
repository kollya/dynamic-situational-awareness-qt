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

#include "AlertSource.h"

using namespace Esri::ArcGISRuntime;

/*!
  \class AlertSource
  \inherits QObject
  \brief Represents a source (generally a real-time feed) for an \l AlertCondition.

  \note This is an abstract base type.
  */

/*!
  \brief Constructor taking an optional \a parent.
 */
AlertSource::AlertSource(QObject* parent):
  QObject(parent)
{

}

/*!
  \brief Destructor.
 */
AlertSource::~AlertSource()
{
  emit noLongerValid();
}