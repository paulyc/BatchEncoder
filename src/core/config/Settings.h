﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <string>
#include "utilities\Utilities.h"

namespace config
{
    class CSettings
    {
    public:
        std::wstring szPortableFile;
    public:
        std::wstring szConfigDir;
        std::wstring szFormatsDir;
        std::wstring szLanguagesDir;
        std::wstring szProgressDir;
        std::wstring szToolsDir;
    public:
        std::wstring szOptionsFileName;
        std::wstring szItemsFileName;
    public:
        std::wstring szSettingsPath;
        std::wstring szFormatsPath;
        std::wstring szLanguagesPath;
        std::wstring szProgressPath;
        std::wstring szToolsPath;
    public:
        std::wstring szOptionsFile;
        std::wstring szItemsFile;
    public:
        CSettings()
        {
            this->szPortableFile = L"BatchEncoder.portable";

            this->szConfigDir = L"BatchEncoder";

            this->szFormatsDir = L"formats";
            this->szLanguagesDir = L"lang";
            this->szProgressDir = L"progress";
            this->szToolsDir = L"tools";

            this->szOptionsFileName = L"Options.xml";
            this->szItemsFileName = L"Items.xml";
        }
    public:
        bool IsPortable()
        {
            std::wstring szPath = util::Utilities::GetExeFilePath() + this->szPortableFile;
            return ::PathFileExists(szPath.c_str()) == TRUE;
        }
    public:
        void InitPortableSettings()
        {
            this->szSettingsPath = util::Utilities::GetExeFilePath();
            this->szFormatsPath = util::Utilities::CombinePath(this->szSettingsPath, this->szFormatsDir);
            this->szLanguagesPath = util::Utilities::CombinePath(this->szSettingsPath, this->szLanguagesDir);
            this->szProgressPath = util::Utilities::CombinePath(this->szSettingsPath, this->szProgressDir);
            this->szToolsPath = util::Utilities::CombinePath(this->szSettingsPath, this->szToolsDir);

            try
            {
                ::CreateDirectory(this->szFormatsPath.c_str(), nullptr);
                ::CreateDirectory(this->szLanguagesPath.c_str(), nullptr);
                ::CreateDirectory(this->szProgressPath.c_str(), nullptr);
                ::CreateDirectory(this->szToolsPath.c_str(), nullptr);
            }
            catch (...) {}

            this->szOptionsFile = util::Utilities::CombinePath(this->szSettingsPath, this->szOptionsFileName);
            this->szItemsFile = util::Utilities::CombinePath(this->szSettingsPath, this->szItemsFileName);
        }
        void InitUserSettings()
        {
            this->szSettingsPath = util::Utilities::GetSettingsFilePath(L"", this->szConfigDir);
            this->szFormatsPath = util::Utilities::GetSettingsFilePath(L"", this->szConfigDir + L"\\" + this->szFormatsDir);
            this->szLanguagesPath = util::Utilities::GetSettingsFilePath(L"", this->szConfigDir + L"\\" + this->szLanguagesDir);
            this->szProgressPath = util::Utilities::GetSettingsFilePath(L"", this->szConfigDir + L"\\" + this->szProgressDir);
            this->szToolsPath = util::Utilities::GetSettingsFilePath(L"", this->szConfigDir + L"\\" + this->szToolsDir);

            try
            {
                ::CreateDirectory(szSettingsPath.c_str(), nullptr);
                ::CreateDirectory(szFormatsPath.c_str(), nullptr);
                ::CreateDirectory(szLanguagesPath.c_str(), nullptr);
                ::CreateDirectory(szProgressPath.c_str(), nullptr);
                ::CreateDirectory(szToolsPath.c_str(), nullptr);
            }
            catch (...) {}

            this->szOptionsFile = util::Utilities::GetSettingsFilePath(this->szOptionsFileName, this->szConfigDir);
            this->szItemsFile = util::Utilities::GetSettingsFilePath(this->szItemsFileName, this->szConfigDir);
        }
    public:
        void Init()
        {
            if (this->IsPortable())
                this->InitPortableSettings();
            else
                this->InitUserSettings();
        }
    };
}
