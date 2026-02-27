#pragma once

#include "Macro.h"
#include <QString>
#include <QVector>
#include <QDomDocument>

namespace NotepadPlusPlus {

/**
 * @brief Handles persistent storage of macros in XML format
 *
 * Stores macros in ~/.config/notepad-plus-plus/macros.xml
 * Compatible with Notepad++ macro format for potential import/export
 *
 * File format:
 * <NotepadPlus>
 *     <Macros>
 *         <Macro name="..." Ctrl="yes" Alt="no" Shift="no" Key="83">
 *             <Action type="1" message="2170" wParam="0" lParam="0" sParam="" />
 *         </Macro>
 *     </Macros>
 * </NotepadPlus>
 */
class MacroStorage
{
public:
    /**
     * @brief Get the path to the macros XML file
     * @return Full path to ~/.config/notepad-plus-plus/macros.xml
     */
    static QString macroFilePath();

    /**
     * @brief Get the directory containing macro files
     * @return Full path to ~/.config/notepad-plus-plus/
     */
    static QString macroDirectory();

    /**
     * @brief Load all macros from XML file
     * @return Vector of macros, or empty vector if file doesn't exist
     */
    static QVector<Macro> loadMacros();

    /**
     * @brief Save all macros to XML file
     * @param macros Vector of macros to save
     * @return true if successful, false on error
     */
    static bool saveMacros(const QVector<Macro>& macros);

    /**
     * @brief Add a single macro to storage
     * @param macro The macro to add
     * @return true if successful, false on error
     */
    static bool addMacro(const Macro& macro);

    /**
     * @brief Update an existing macro by name
     * @param name The name of the macro to update
     * @param macro The updated macro data
     * @return true if successful, false if macro not found
     */
    static bool updateMacro(const QString& name, const Macro& macro);

    /**
     * @brief Delete a macro by name
     * @param name The name of the macro to delete
     * @return true if successful, false if macro not found
     */
    static bool deleteMacro(const QString& name);

    /**
     * @brief Check if a macro exists by name
     * @param name The name of the macro to check
     * @return true if macro exists
     */
    static bool hasMacro(const QString& name);

    /**
     * @brief Get a single macro by name
     * @param name The name of the macro to retrieve
     * @return The macro, or an invalid macro if not found
     */
    static Macro getMacro(const QString& name);

    /**
     * @brief Create backup of macros file
     * @return true if successful
     */
    static bool createBackup();

    /**
     * @brief Restore from backup file
     * @return true if successful
     */
    static bool restoreFromBackup();

private:
    /**
     * @brief Create an empty XML document structure
     * @return Empty QDomDocument with root elements
     */
    static QDomDocument createEmptyDocument();

    /**
     * @brief Load XML document from file
     * @return QDomDocument, or empty document if file doesn't exist/is invalid
     */
    static QDomDocument loadDocument();

    /**
     * @brief Save XML document to file
     * @param doc The document to save
     * @return true if successful, false on error
     */
    static bool saveDocument(const QDomDocument& doc);

    /**
     * @brief Ensure macro directory exists
     * @return true if directory exists or was created
     */
    static bool ensureDirectoryExists();
};

} // namespace NotepadPlusPlus
