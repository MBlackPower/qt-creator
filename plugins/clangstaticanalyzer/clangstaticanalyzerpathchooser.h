/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://www.qt.io/contact-us
**
** This file is part of the Qt Enterprise LicenseChecker Add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io/contact-us
**
****************************************************************************/
#ifndef QTC_CLANGSTATICANALYZER_PATHCHOOSER_H
#define QTC_CLANGSTATICANALYZER_PATHCHOOSER_H

#include <utils/pathchooser.h>

namespace ClangStaticAnalyzer {
namespace Internal {

class PathChooser : public Utils::PathChooser
{
    Q_OBJECT

public:
    PathChooser(QWidget *parent = 0);

private:
    bool validatePath(const QString &path, QString *errorMessage = 0);
};

} // namespace Internal
} // namespace ClangStaticAnalyzer

#endif // Include guard.
