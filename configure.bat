:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
:: All rights reserved.
:: Contact: Nokia Corporation (qt-info@nokia.com)
::
:: This file is part of the Qt Components project on Qt Labs.
::
:: No Commercial Usage
:: This file contains pre-release code and may not be distributed.
:: You may use this file in accordance with the terms and conditions contained
:: in the Technology Preview License Agreement accompanying this package.
::
:: GNU Lesser General Public License Usage
:: Alternatively, this file may be used under the terms of the GNU Lesser
:: General Public License version 2.1 as published by the Free Software
:: Foundation and appearing in the file LICENSE.LGPL included in the
:: packaging of this file.  Please review the following information to
:: ensure the GNU Lesser General Public License version 2.1 requirements
:: will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
::
:: If you have questions regarding the use of this file, please contact
:: Nokia at qt-info@nokia.com.
::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@echo off

set BUILD_TREE=%CD%
set SOURCE_TREE=%~dp0
cd /D %SOURCE_TREE%
set SOURCE_TREE=%CD%
cd /D %BUILD_TREE%

set QMAKE=qmake
if not "%QTDIR%" == "" set QMAKE=%QTDIR%\bin\qmake

set QMAKE_CACHE=%BUILD_TREE%\.qmake.cache
if exist "%QMAKE_CACHE%" del /Q %QMAKE_CACHE%

echo Q_COMPONENTS_SOURCE_TREE = %SOURCE_TREE:\=/% > %QMAKE_CACHE%
echo Q_COMPONENTS_BUILD_TREE = %BUILD_TREE:\=/% >> %QMAKE_CACHE%

echo.
echo Running qmake...
call %QMAKE% -r %* %SOURCE_TREE%\qt-components.pro 2> NUL
if errorlevel 1 echo ERROR: Unable to detect qmake. Set QTDIR=\path\to\qt and re-run configure.bat.
