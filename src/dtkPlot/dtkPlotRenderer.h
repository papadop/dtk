/* dtkPlotRenderer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jul  4 21:11:19 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul  4 21:28:40 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTRENDERER_H
#define DTKPLOTRENDERER_H

#include <qwt_plot_renderer.h>

class dtkPlotRendererPrivate;
class dtkPlotView;

class dtkPlotRenderer
{
public:
     dtkPlotRenderer(void);
    ~dtkPlotRenderer(void);

public:
    void render(void);

public:
    void setView(dtkPlotView *view);
    void setSize(const QSize& size);
    void setPath(const QString& path);

private:
    dtkPlotRendererPrivate *d;
};

#endif
