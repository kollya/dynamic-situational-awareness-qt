/*******************************************************************************
 *  Copyright 2012-2018 Esri
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ******************************************************************************/

// PCH header
#include "pch.hpp"

#include "DataItemListModel.h"

// Qt headers
#include <QAbstractListModel>
#include <QByteArray>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QVariant>

namespace Dsa {

/*!
  \class Dsa::DataItemListModel
  \inmodule Dsa
  \inherits QAbstractListModel
  \brief A model responsible for storing data items (such as local layers) and reporting when they
  change.

  The model returns data for the following roles:
  \table
    \header
        \li Role
        \li Type
        \li Description
    \row
        \li fullPath
        \li QString
        \li The full path to the data item.
    \row
        \li fileName
        \li QString
        \li The file name of the data item.
  \endtable
 */

/*!
  \brief Constructor for a model taking an optional \a parent.
 */
DataItemListModel::DataItemListModel(QObject* parent) :
  QAbstractListModel(parent)
{
  setupRoles();
}

/*!
  \internal
 */
void DataItemListModel::setupRoles()
{
  m_roles[FullPathRole] = "fullPath";
  m_roles[FileNameRole] = "fileName";
}

/*!
  \brief Adds a new local data item located at \a fullPath.
 */
void DataItemListModel::addDataItem(const QString& fullPath)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_dataItems.append(fullPath);
  endInsertRows();
}

/*!
  \brief Returns the number of data items in the model.

  \list
  \li \a parent - The parent object (unused).
  \endlist
 */
int DataItemListModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return m_dataItems.count();
}

/*!
  \brief Returns the data stored under \a role at \a index in the model.

  The role should make use of the \l DataItemRoles enum.
 */
QVariant DataItemListModel::data(const QModelIndex& index, int role) const
{
  if (index.row() < 0 || index.row() >= m_dataItems.count())
    return QVariant();

  DataItem dataItem = m_dataItems[index.row()];

  QVariant retVal;

  switch (role)
  {
  case FullPathRole:
    retVal = dataItem.fullPath;
    break;
  case FileNameRole:
    retVal = dataItem.fileName;
    break;
  default:
    break;
  }

  return retVal;
}

/*!
  \brief Returns the hash of role names used by the model.

  The roles are based on the \l DataItemRoles enum.
 */
QHash<int, QByteArray> DataItemListModel::roleNames() const
{
  return m_roles;
}

/*!
  \brief Clears the model.
 */
void DataItemListModel::clear()
{
  beginResetModel();
  m_dataItems.clear();
  endResetModel();
}

/*!
  \brief Returns the \l DataType of the item at \a index in the model.
 */
DataType DataItemListModel::getDataItemType(int index)
{
  if (index >= m_dataItems.size())
    return DataType::Unknown;

  return m_dataItems.at(index).dataType;
}

/*!
  \brief Returns the path of the item at \a index in the model.
 */
QString DataItemListModel::getDataItemPath(int index) const
{
  if (index >= m_dataItems.size())
    return QString();

  return m_dataItems.at(index).fullPath;
}

/*!
  \internal
  c'tor for DataItem struct
 */
DataItemListModel::DataItem::DataItem(const QString& fullPath):
  fullPath(fullPath)
{
  // set the file name
  QFileInfo fileInfo(fullPath);
  fileName = fileInfo.fileName();

  // determine the layer type
  QString fileExtension = fileInfo.completeSuffix();
  QStringList rasterExtensions{"img", "tif", "tiff", "i1", "dt0", "dt1", "dt2", "tc2", "geotiff", "hr1", "jpg", "jpeg", "jp2", "ntf", "png", "i21", "sid"};
  if (fileExtension == "geodatabase")
    dataType = DataType::Geodatabase;
  else if (fileExtension.compare("tpk", Qt::CaseInsensitive) == 0)
    dataType = DataType::TilePackage;
  else if (fileExtension.compare("shp", Qt::CaseInsensitive) == 0)
    dataType = DataType::Shapefile;
  else if (fileExtension.compare("gpkg", Qt::CaseInsensitive) == 0)
    dataType = DataType::GeoPackage;
  else if (fileExtension.compare("slpk", Qt::CaseInsensitive) == 0)
    dataType = DataType::SceneLayerPackage;
  else if (fileExtension.compare("vtpk", Qt::CaseInsensitive) == 0)
    dataType = DataType::VectorTilePackage;
  else if (fileExtension.compare("markup", Qt::CaseInsensitive) == 0)
    dataType = DataType::Markup;
  else if ((fileExtension.compare("kml", Qt::CaseInsensitive) == 0) || (fileExtension.compare("kmz", Qt::CaseInsensitive) == 0))
    dataType = DataType::Kml;
  else if (rasterExtensions.contains(fileExtension.toLower()))
    dataType = DataType::Raster;
  else
    dataType = DataType::Unknown;
}

} // Dsa

