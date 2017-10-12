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

#ifndef MESSAGESOVERLAY_H
#define MESSAGESOVERLAY_H

#include <QObject>
#include <QPointer>

namespace Esri
{
  namespace ArcGISRuntime
  {
    class GeoView;
    class Renderer;
    class GraphicsOverlay;
    class Graphic;
  }
}

class Message;

class MessagesOverlay : public QObject
{
  Q_OBJECT

public:
  explicit MessagesOverlay(Esri::ArcGISRuntime::GeoView* geoView, QObject* parent = nullptr);
  MessagesOverlay(Esri::ArcGISRuntime::GeoView* geoView, Esri::ArcGISRuntime::Renderer* renderer, QObject* parent = nullptr);
  ~MessagesOverlay();

  Esri::ArcGISRuntime::Renderer* renderer() const;
  void setRenderer(Esri::ArcGISRuntime::Renderer* renderer);

  QList<Esri::ArcGISRuntime::GraphicsOverlay*> graphicsOverlays() const;

  Esri::ArcGISRuntime::GeoView* geoView() const;

  bool addMessage(const Message& message);

  bool isVisible() const;
  void setVisible(bool visible);

signals:
  void graphicsOverlaysChanged();
  void visibleChanged();
  void errorOccurred(const QString& error);

private:
  Q_DISABLE_COPY(MessagesOverlay)

  Esri::ArcGISRuntime::GeoView* m_geoView = nullptr;
  QPointer<Esri::ArcGISRuntime::Renderer> m_renderer;
  QList<Esri::ArcGISRuntime::GraphicsOverlay*> m_graphicsOverlays;

  Esri::ArcGISRuntime::GraphicsOverlay* m_pointGraphicsOverlay = nullptr;
  Esri::ArcGISRuntime::GraphicsOverlay* m_linePolygonGraphicsOverlay = nullptr;

  QHash<QString, Esri::ArcGISRuntime::Graphic*> m_existingGraphics;
};

#endif // MESSAGESOVERLAY_H
