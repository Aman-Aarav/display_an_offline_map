// Copyright 2024 ESRI
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

#ifndef DISPLAY_AN_OFFLINE_MAP_H
#define DISPLAY_AN_OFFLINE_MAP_H

namespace Esri::ArcGISRuntime {
class Map;
class MapQuickView;
class PortalItem;
class OfflineMapTask;
} // namespace Esri::ArcGISRuntime

#include <QObject>

Q_MOC_INCLUDE("MapQuickView.h")

class Display_an_offline_map : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)

public:
    explicit Display_an_offline_map(QObject* parent = nullptr);
    ~Display_an_offline_map() override;

signals:
    void mapViewChanged();

private:
    Esri::ArcGISRuntime::MapQuickView* mapView() const;
    void setMapView(Esri::ArcGISRuntime::MapQuickView* mapView);
     void generateMapByExtent();

    Esri::ArcGISRuntime::Map* m_map = nullptr;
    Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;

    Esri::ArcGISRuntime::PortalItem* m_portalItem = nullptr;
    Esri::ArcGISRuntime::OfflineMapTask* m_offlineMapTask = nullptr;
};

#endif // DISPLAY_AN_OFFLINE_MAP_H
