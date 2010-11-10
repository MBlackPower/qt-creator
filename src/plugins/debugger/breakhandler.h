/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef DEBUGGER_BREAKHANDLER_H
#define DEBUGGER_BREAKHANDLER_H

#include "breakpoint.h"

#include <QtCore/QObject>
#include <QtCore/QAbstractTableModel>

#include <QtGui/QIcon>

namespace Debugger {

class DebuggerEngine;

namespace Internal {

//////////////////////////////////////////////////////////////////
//
// BreakHandler
//
//////////////////////////////////////////////////////////////////

class BreakHandler : public QAbstractTableModel
{
    Q_OBJECT

public:
    BreakHandler();
    ~BreakHandler();

    void removeAllBreakpoints();
    void loadSessionData();
    void saveSessionData();

    QAbstractItemModel *model() { return this; }

    BreakpointData *at(int index) const;
    int size() const;
    bool hasPendingBreakpoints() const;
    void removeAt(int index); // This also deletes the marker.
    void clear(); // This also deletes all the marker.
    int indexOf(BreakpointData *data);
    // Find a breakpoint matching approximately the data in needle.
    BreakpointData *findSimilarBreakpoint(const BreakpointData *needle) const;
    BreakpointData *findBreakpointByNumber(int bpNumber) const;
    int findWatchPointIndexByAddress(quint64 address) const;
    bool watchPointAt(quint64 address) const;
    void updateMarkers();
    void updateMarker(BreakpointData *);
    void removeMarker(BreakpointData *);
    bool isActive() const;

    Breakpoints takeRemovedBreakpoints(); // Owned.
    Breakpoints takeEnabledBreakpoints(); // Not owned.
    Breakpoints takeDisabledBreakpoints(); // Not owned.

    QIcon breakpointIcon() const { return m_breakpointIcon; }
    QIcon disabledBreakpointIcon() const { return m_disabledBreakpointIcon; }
    QIcon pendingBreakPointIcon() const { return m_pendingBreakPointIcon; }
    QIcon emptyIcon() const { return m_emptyIcon; }

    void toggleBreakpoint(const QString &fileName, int lineNumber, quint64 address = 0);
    void toggleBreakpointEnabled(const QString &fileName, int lineNumber);
    BreakpointData *findBreakpoint(const QString &fileName, int lineNumber,
        bool useMarkerPosition = true);
    BreakpointData *findBreakpoint(quint64 address) const;

    void appendBreakpoint(BreakpointData *data);
    void reinsertBreakpoint(BreakpointData *data);
    void toggleBreakpointEnabled(BreakpointData *data);
    void breakByFunction(const QString &functionName);
    void removeBreakpoint(int index);
    void removeBreakpoint(BreakpointData *data);
    void synchronizeBreakpoints();

signals:
    void breakpointSynchronizationRequested();

private:
    friend class BreakpointMarker;

    // QAbstractItemModel
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void markerUpdated(BreakpointMarker *marker, int lineNumber);
    void loadBreakpoints();
    void saveBreakpoints();
    void removeBreakpointHelper(int index);
    void append(BreakpointData *data);

    const QIcon m_breakpointIcon;
    const QIcon m_disabledBreakpointIcon;
    const QIcon m_pendingBreakPointIcon;
    const QIcon m_emptyIcon;
    const QIcon m_watchpointIcon;

    Breakpoints m_inserted; // Lately inserted breakpoints.
    Breakpoints m_removed; // Lately removed breakpoints.
    Breakpoints m_enabled; // Lately enabled breakpoints.
    Breakpoints m_disabled; // Lately disabled breakpoints.

    // Hack for BreakWindow::findSimilarBreakpoint
    mutable BreakpointData *m_lastFound;
    mutable bool m_lastFoundQueried;

    Breakpoints m_bp;
    QHash<quint64, BreakpointMarker *> m_markers;
};

} // namespace Internal
} // namespace Debugger

#endif // DEBUGGER_BREAKHANDLER_H
