/*
 * Copyright (C) 2021 Anton Filimonov and other contributors
 *
 * This file is part of klogg.
 *
 * klogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * klogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with klogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <map>

#include <QApplication>
#include <QPalette>
#include <QStyleFactory>
#include <qcolor.h>

#include "configuration.h"
#include "log.h"
#include "styles.h"

namespace {

using ThemeColors = std::map<QString, QString>;

const std::map<QString, ThemeColors>& builtinThemes()
{
    static const std::map<QString, ThemeColors> themes = {
        { "One Dark",
          {
              { "Window", "#21252b" },
              { "WindowText", "#abb2bf" },
              { "Base", "#282c34" },
              { "AlternateBase", "#2c313c" },
              { "ToolTipBase", "#353b45" },
              { "ToolTipText", "#e6e6e6" },
              { "Text", "#abb2bf" },
              { "Button", "#2c313c" },
              { "ButtonText", "#abb2bf" },
              { "Link", "#61afef" },
              { "Highlight", "#3e4451" },
              { "HighlightedText", "#e6e6e6" },
              { "ActiveButton", "#353b45" },
              { "DisabledButtonText", "#7a8494" },
              { "DisabledWindowText", "#7a8494" },
              { "DisabledText", "#7a8494" },
              { "DisabledLight", "#2c313c" },
          } },
        { "Dracula",
          {
              { "Window", "#21222c" },
              { "WindowText", "#f8f8f2" },
              { "Base", "#282a36" },
              { "AlternateBase", "#2b2d3a" },
              { "ToolTipBase", "#44475a" },
              { "ToolTipText", "#f8f8f2" },
              { "Text", "#f8f8f2" },
              { "Button", "#44475a" },
              { "ButtonText", "#f8f8f2" },
              { "Link", "#8be9fd" },
              { "Highlight", "#44475a" },
              { "HighlightedText", "#f8f8f2" },
              { "ActiveButton", "#4d5066" },
              { "DisabledButtonText", "#7b86a8" },
              { "DisabledWindowText", "#7b86a8" },
              { "DisabledText", "#7b86a8" },
              { "DisabledLight", "#44475a" },
          } },
        { "Nord",
          {
              { "Window", "#272c36" },
              { "WindowText", "#e5e9f0" },
              { "Base", "#2e3440" },
              { "AlternateBase", "#3b4252" },
              { "ToolTipBase", "#434c5e" },
              { "ToolTipText", "#eceff4" },
              { "Text", "#d8dee9" },
              { "Button", "#3b4252" },
              { "ButtonText", "#eceff4" },
              { "Link", "#88c0d0" },
              { "Highlight", "#4c566a" },
              { "HighlightedText", "#eceff4" },
              { "ActiveButton", "#434c5e" },
              { "DisabledButtonText", "#8491aa" },
              { "DisabledWindowText", "#8491aa" },
              { "DisabledText", "#8491aa" },
              { "DisabledLight", "#3b4252" },
          } },
        { "Tokyo Night",
          {
              { "Window", "#16161e" },
              { "WindowText", "#c0caf5" },
              { "Base", "#1a1b26" },
              { "AlternateBase", "#1f2335" },
              { "ToolTipBase", "#292e42" },
              { "ToolTipText", "#c0caf5" },
              { "Text", "#c0caf5" },
              { "Button", "#292e42" },
              { "ButtonText", "#c0caf5" },
              { "Link", "#7aa2f7" },
              { "Highlight", "#283457" },
              { "HighlightedText", "#c0caf5" },
              { "ActiveButton", "#343b58" },
              { "DisabledButtonText", "#737aa2" },
              { "DisabledWindowText", "#737aa2" },
              { "DisabledText", "#737aa2" },
              { "DisabledLight", "#292e42" },
          } },
        { "Gruvbox Dark",
          {
              { "Window", "#1d2021" },
              { "WindowText", "#ebdbb2" },
              { "Base", "#282828" },
              { "AlternateBase", "#32302f" },
              { "ToolTipBase", "#3c3836" },
              { "ToolTipText", "#ebdbb2" },
              { "Text", "#ebdbb2" },
              { "Button", "#3c3836" },
              { "ButtonText", "#ebdbb2" },
              { "Link", "#83a598" },
              { "Highlight", "#504945" },
              { "HighlightedText", "#fbf1c7" },
              { "ActiveButton", "#504945" },
              { "DisabledButtonText", "#928374" },
              { "DisabledWindowText", "#928374" },
              { "DisabledText", "#928374" },
              { "DisabledLight", "#3c3836" },
          } },
        { "Catppuccin Mocha",
          {
              { "Window", "#11111b" },
              { "WindowText", "#cdd6f4" },
              { "Base", "#1e1e2e" },
              { "AlternateBase", "#181825" },
              { "ToolTipBase", "#313244" },
              { "ToolTipText", "#cdd6f4" },
              { "Text", "#cdd6f4" },
              { "Button", "#313244" },
              { "ButtonText", "#cdd6f4" },
              { "Link", "#89b4fa" },
              { "Highlight", "#585b70" },
              { "HighlightedText", "#cdd6f4" },
              { "ActiveButton", "#45475a" },
              { "DisabledButtonText", "#7f849c" },
              { "DisabledWindowText", "#7f849c" },
              { "DisabledText", "#7f849c" },
              { "DisabledLight", "#45475a" },
          } },
        { "GitHub Dark",
          {
              { "Window", "#161b22" },
              { "WindowText", "#c9d1d9" },
              { "Base", "#0d1117" },
              { "AlternateBase", "#161b22" },
              { "ToolTipBase", "#21262d" },
              { "ToolTipText", "#c9d1d9" },
              { "Text", "#c9d1d9" },
              { "Button", "#21262d" },
              { "ButtonText", "#c9d1d9" },
              { "Link", "#58a6ff" },
              { "Highlight", "#264f78" },
              { "HighlightedText", "#FFFFFF" },
              { "ActiveButton", "#30363d" },
              { "DisabledButtonText", "#8b949e" },
              { "DisabledWindowText", "#8b949e" },
              { "DisabledText", "#8b949e" },
              { "DisabledLight", "#30363d" },
          } },
    };

    return themes;
}

} // namespace

QStringList StyleManager::availableStyles()
{
    QStringList styles;
#ifdef Q_OS_WIN
    styles << VistaKey;
    styles << WindowsKey;
    styles << FusionKey;
#else
    styles << QStyleFactory::keys();
#endif

    auto removedStyles = std::remove_if( styles.begin(), styles.end(), []( const QString& style ) {
        return style.startsWith( Gtk2Key, Qt::CaseInsensitive )
               || style.startsWith( Bb10Key, Qt::CaseInsensitive );
    } );

    styles.erase( removedStyles, styles.end() );

    styles << DarkStyleKey;

#ifndef Q_OS_MACOS
    styles << DarkWindowsStyleKey;
#endif

    std::sort( styles.begin(), styles.end(), []( const auto& lhs, const auto& rhs ) {
        return lhs.compare( rhs, Qt::CaseInsensitive ) < 0;
    } );

    return styles;
}

QString StyleManager::defaultPlatformStyle()
{
#if defined( Q_OS_WIN )
    return VistaKey;
#elif defined( Q_OS_MACOS )
    return MacintoshKey;
#else
    return FusionKey;
#endif
}

QStringList StyleManager::availableThemes()
{
    QStringList themes;
    themes << DefaultThemeKey;

    for ( const auto& theme : builtinThemes() ) {
        themes << theme.first;
    }

    return themes;
}

QString StyleManager::defaultTheme()
{
    return DefaultThemeKey;
}

bool StyleManager::isDarkStyle( const QString& style )
{
    return style == DarkStyleKey || style == DarkWindowsStyleKey;
}

std::map<QString, QString> StyleManager::themePalette( const QString& theme )
{
    if ( theme.isEmpty() || theme == DefaultThemeKey ) {
        return Configuration::get().darkPalette();
    }

    const auto& themes = builtinThemes();
    const auto found = themes.find( theme );
    if ( found == themes.end() ) {
        return Configuration::get().darkPalette();
    }

    return found->second;
}

void StyleManager::applyStyle( const QString& style, const QString& theme )
{
    LOG_INFO << "Setting style to " << style << ", theme " << theme;

    if ( isDarkStyle( style ) ) {
        const auto palette = themePalette( theme );
        if ( palette.empty() ) {
            return;
        }

        QPalette darkPalette;
        darkPalette.setColor( QPalette::Window, QColor( palette.at( "Window" ) ) );
        darkPalette.setColor( QPalette::WindowText, QColor( palette.at( "WindowText" ) ) );
        darkPalette.setColor( QPalette::Base, QColor( palette.at( "Base" ) ) );
        darkPalette.setColor( QPalette::AlternateBase, QColor( palette.at( "AlternateBase" ) ) );
        darkPalette.setColor( QPalette::ToolTipBase, QColor( palette.at( "ToolTipBase" ) ) );
        darkPalette.setColor( QPalette::ToolTipText, QColor( palette.at( "ToolTipText" ) ) );
        darkPalette.setColor( QPalette::Text, QColor( palette.at( "Text" ) ) );
        darkPalette.setColor( QPalette::Button, QColor( palette.at( "Button" ) ) );
        darkPalette.setColor( QPalette::ButtonText, QColor( palette.at( "ButtonText" ) ) );
        darkPalette.setColor( QPalette::Link, QColor( palette.at( "Link" ) ) );
        darkPalette.setColor( QPalette::Highlight, QColor( palette.at( "Highlight" ) ) );
        darkPalette.setColor( QPalette::HighlightedText,
                              QColor( palette.at( "HighlightedText" ) ) );

        darkPalette.setColor( QPalette::Active, QPalette::Button,
                              QColor( palette.at( "ActiveButton" ) ) );
        darkPalette.setColor( QPalette::Disabled, QPalette::ButtonText,
                              QColor( palette.at( "DisabledButtonText" ) ) );
        darkPalette.setColor( QPalette::Disabled, QPalette::WindowText,
                              QColor( palette.at( "DisabledWindowText" ) ) );
        darkPalette.setColor( QPalette::Disabled, QPalette::Text,
                              QColor( palette.at( "DisabledText" ) ) );
        darkPalette.setColor( QPalette::Disabled, QPalette::Light,
                              QColor( palette.at( "DisabledLight" ) ) );

        if ( style == DarkWindowsStyleKey ) {
            qApp->setStyle( QStyleFactory::create( WindowsKey ) );
        }
        else {
            qApp->setStyle( QStyleFactory::create( FusionKey ) );
        }

        qApp->setPalette( darkPalette );
    }
    else {
        qApp->setStyle( style );
        qApp->setStyleSheet( "" );
    }
}
