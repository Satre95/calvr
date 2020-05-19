#include <cvrKernel/ScreenStereo.h>
#include <cvrKernel/CVRViewer.h>

#include <osgViewer/Renderer>

#include <iostream>

using namespace cvr;

ScreenStereo::ScreenStereo() :
        ScreenBase()
{
}

ScreenStereo::~ScreenStereo()
{
}

void ScreenStereo::init(int mode)
{
    _stereoMode = (osg::DisplaySettings::StereoMode)mode;

    _camera = new osg::Camera();

    osg::DisplaySettings * ds = new osg::DisplaySettings();
    _camera->setDisplaySettings(ds);

    CVRViewer::instance()->addSlave(_camera.get(),osg::Matrixd(),
            osg::Matrixd());
    defaultCameraInit(_camera.get());

    osgViewer::Renderer * renderer =
            dynamic_cast<osgViewer::Renderer*>(_camera->getRenderer());
    if(!renderer)
    {
        std::cerr << "Error getting renderer pointer." << std::endl;
    }
    else
    {
        osg::DisplaySettings * ds =
                renderer->getSceneView(0)->getDisplaySettings();
        ds->setStereo(true);
        ds->setStereoMode(_stereoMode);
        if (_myInfo->myChannel->swapStereoEyes)
        {
            if (_stereoMode == osg::DisplaySettings::VERTICAL_SPLIT)
            {
                ds->setSplitStereoVerticalEyeMapping(osg::DisplaySettings::LEFT_EYE_BOTTOM_VIEWPORT);
            }
            else if (_stereoMode == osg::DisplaySettings::HORIZONTAL_SPLIT)
            {
                ds->setSplitStereoHorizontalEyeMapping(osg::DisplaySettings::LEFT_EYE_RIGHT_VIEWPORT);
            }
        }
        StereoCallback * sc = new StereoCallback;
        sc->screen = this;
        renderer->getSceneView(0)->setComputeStereoMatricesCallback(sc);
        renderer->getSceneView(1)->setComputeStereoMatricesCallback(sc);
    }
}

void ScreenStereo::computeViewProj()
{
    osg::Vec3d eyeLeft = defaultLeftEye(_myInfo->myChannel->head);
    osg::Vec3d eyeRight = defaultRightEye(_myInfo->myChannel->head);

    computeDefaultViewProj(eyeLeft,_viewLeft,_projLeft);
    computeDefaultViewProj(eyeRight,_viewRight,_projRight);
}

void ScreenStereo::updateCamera()
{
    // not needed for this mode
}

osg::Matrixd ScreenStereo::StereoCallback::computeLeftEyeProjection(
        const osg::Matrixd &projection) const
{
    (void)projection;
    return screen->_projLeft;
}

osg::Matrixd ScreenStereo::StereoCallback::computeLeftEyeView(
        const osg::Matrixd &view) const
{
    (void)view;
    return screen->_viewLeft;
}

osg::Matrixd ScreenStereo::StereoCallback::computeRightEyeProjection(
        const osg::Matrixd &projection) const
{
    (void)projection;
    return screen->_projRight;
}

osg::Matrixd ScreenStereo::StereoCallback::computeRightEyeView(
        const osg::Matrixd &view) const
{
    (void)view;
    return screen->_viewRight;
}

void ScreenStereo::setClearColor(osg::Vec4 color)
{
    _camera->setClearColor(color);
}

ScreenInfo * ScreenStereo::findScreenInfo(osg::Camera * c)
{
    if(c == _camera.get())
    {
        return _myInfo;
    }
    return NULL;
}

void ScreenStereo::adjustViewportCoords(int & x, int & y)
{
    if(_stereoMode == osg::DisplaySettings::HORIZONTAL_SPLIT)
    {
        if(x > (_myInfo->myChannel->width / 2.0))
        {
            x = (int)(((float)x) - (_myInfo->myChannel->width / 2.0));
        }
        x *= 2;
    }
    else if(_stereoMode == osg::DisplaySettings::VERTICAL_SPLIT)
    {
        if(y > (_myInfo->myChannel->height / 2.0))
        {
            y = (int)(((float)y) - (_myInfo->myChannel->height / 2.0));
        }
        y *= 2;
    }

    return;
}

void ScreenStereo::viewportResized(int left, int bottom, int width, int height)
{
    if(_camera)
    {
        osg::Viewport * viewport = _camera->getViewport();
        if(viewport)
        {
            viewport->x() = left;
            viewport->y() = bottom;
            viewport->width() = width;
            viewport->height() = height;
        }
    }
    ScreenBase::viewportResized(left,bottom,width,height);
}

void ScreenStereo::setStereoMode(osg::DisplaySettings::StereoMode sm)
{
    _stereoMode = sm;

    osgViewer::Renderer * renderer =
            dynamic_cast<osgViewer::Renderer*>(_camera->getRenderer());
    if(!renderer)
    {
        std::cerr << "Error getting renderer pointer." << std::endl;
    }
    else
    {
        osg::DisplaySettings * ds =
                renderer->getSceneView(0)->getDisplaySettings();
        ds->setStereoMode(_stereoMode);
    }
}
