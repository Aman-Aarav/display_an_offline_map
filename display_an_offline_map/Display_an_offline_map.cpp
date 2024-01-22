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

#include "Display_an_offline_map.h"

#include "Map.h"

#include "MapQuickView.h"
#include "Envelope.h"
#include "EnvelopeBuilder.h"
#include "Error.h"
#include "GenerateOfflineMapParameters.h"
#include "GenerateOfflineMapJob.h"
#include "GenerateOfflineMapResult.h"
#include "Graphic.h"
#include "GraphicListModel.h"
#include "GraphicsOverlay.h"
#include "GraphicsOverlayListModel.h"
#include "OfflineMapTask.h"
#include "Portal.h"
#include "PortalItem.h"
#include "SimpleFillSymbol.h"
#include "SimpleLineSymbol.h"
#include "SpatialReference.h"
#include "SymbolTypes.h"
#include "TaskTypes.h"
#include <QFuture>
#include <QDir>
#include <QUuid>

using namespace Esri::ArcGISRuntime;

Display_an_offline_map::Display_an_offline_map(QObject* parent /* = nullptr */):
    QObject(parent)
{
    Portal* portal = new Portal(false, this);
    m_portalItem = new PortalItem(portal, "acc027394bc84c2fb04d1ed317aac674", this);
    m_map = new Map(m_portalItem, this);
    m_offlineMapTask = new OfflineMapTask(m_portalItem, this);

}

Display_an_offline_map::~Display_an_offline_map()
{
}

MapQuickView* Display_an_offline_map::mapView() const
{
    return m_mapView;
}

// Set the view (created in QML)
void Display_an_offline_map::setMapView(MapQuickView* mapView)
{
    if (!mapView || mapView == m_mapView)
    {
        return;
    }

    m_mapView = mapView;
    m_mapView->setMap(m_map);
    generateMapByExtent();

    emit mapViewChanged();
}

void Display_an_offline_map::generateMapByExtent()
{
    // Create envelope to define area of interest
    EnvelopeBuilder* envelopeBuilder = new EnvelopeBuilder(SpatialReference::wgs84(), this);

    envelopeBuilder->setXMin(-88.1526);
    envelopeBuilder->setXMax(-88.1490);
    envelopeBuilder->setYMin(41.7694);
    envelopeBuilder->setYMax(41.7714);

    Envelope offlineArea = envelopeBuilder->toEnvelope();
    Graphic* box = new Graphic(offlineArea, new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, Qt::transparent, new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, Qt::red, 3, this), this), this);
    GraphicsOverlay* boxOverlay = new GraphicsOverlay(this);
    boxOverlay->graphics()->append(box);

    // add graphics overlay to the map view
    m_mapView->graphicsOverlays()->append(boxOverlay);


}
