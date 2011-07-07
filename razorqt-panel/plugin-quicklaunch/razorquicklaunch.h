/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/projects/razor-qt/
 *
 * Copyright: 2011 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef RAZORQUICKLAUNCH_H
#define RAZORQUICKLAUNCH_H

#include "../panel/razorpanelplugin.h"
#include "../panel/razorpanel.h"
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtGui/QAction>

class XdgDesktopFile;
class QAction;
class QDragEnterEvent;


/*! \brief Loader for "quick launcher" icons in the panel.
\author Petr Vanek <petr@scribus.info>
*/
class RazorQuickLaunch : public RazorPanelPlugin
{
    Q_OBJECT

public:
    RazorQuickLaunch(const RazorPanelPluginStartInfo* startInfo, QWidget* parent = 0);
    ~RazorQuickLaunch();

private:
    QMap<QString,XdgDesktopFile*> m_xdgFiles;

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private slots:
    //! run command in the action
    void execAction(QAction*);
    void addButton(QAction* action);
};

/*! \brief Special action representation for RazorQuickLaunch plugin.
It supports XDG desktop files or "legacy" launching of specified apps.
All process management is handled internally.
\author Petr Vanek <petr@scribus.info>
*/
class RazorQuickLaunchAction : public QAction
{
    Q_OBJECT

public:
    /*! Constructor for "legacy" launchers.
        \warning The XDG way is preferred this is only for older or non-standard apps
        \param name a name to display in tooltip
        \param exec a executable with path
        \param icon a valid QIcon
     */
    RazorQuickLaunchAction(const QString & name,
                           const QString & exec,
                           const QIcon & icon,
                           QWidget * parent);
    /*! Constructor for XDG desktop handlers.
     */
    RazorQuickLaunchAction(const XdgDesktopFile * xdg, QWidget * parent);
    /*! Constructor for regular files 
     */
    RazorQuickLaunchAction(const QString & fileName, QWidget * parent);

    //! Returns true if the action is valid (contains all required properties).
    bool isValid() { return m_valid; }

public slots:
    void execAction();

private:
    enum ActionType { ActionLegacy, ActionXdg, ActionFile };
    ActionType m_type;
    QString m_data;
    bool m_valid;
};

EXPORT_RAZOR_PANEL_PLUGIN_H

#endif
