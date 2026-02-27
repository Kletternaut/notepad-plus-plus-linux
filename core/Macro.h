#pragma once

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QDomElement>
#include <QDomDocument>
#include <QKeySequence>

namespace NotepadPlusPlus {

/**
 * @brief Represents a single action in a macro
 *
 * Actions can be of different types:
 * - Type 1: Scintilla messages (SCI_* commands for text editing)
 * - Type 2: Menu commands (application-level actions)
 * - Type 3: Find/replace operations
 */
struct MacroAction
{
    int type = 1;              // Action type (1=Scintilla, 2=Menu, 3=Find)
    unsigned int message = 0;  // Scintilla message ID or command ID
    unsigned long wParam = 0;  // First parameter
    long lParam = 0;           // Second parameter
    QString sParam;            // String parameter (text, search terms, etc.)

    /**
     * @brief Convert action to XML element
     * @param doc The XML document
     * @return QDomElement representing this action
     */
    QDomElement toXml(QDomDocument& doc) const;

    /**
     * @brief Create action from XML element
     * @param element The XML element to parse
     * @return MacroAction parsed from XML
     */
    static MacroAction fromXml(const QDomElement& element);

    /**
     * @brief Check if action is valid
     * @return true if action has required fields
     */
    bool isValid() const;
};

/**
 * @brief Represents a complete macro with actions and metadata
 *
 * Matches Notepad++ XML format for compatibility:
 * <Macro name="..." Ctrl="yes/no" Alt="yes/no" Shift="yes/no" Key="123">
 *     <Action type="1" message="2170" wParam="0" lParam="0" sParam="" />
 * </Macro>
 */
struct Macro
{
    QString name;              // Macro name (unique identifier)
    QString description;       // Optional description
    QDateTime created;         // Creation timestamp
    QDateTime modified;        // Last modification timestamp
    QVector<MacroAction> actions;  // Sequence of actions

    // Keyboard shortcut (Notepad++ compatible)
    bool ctrlKey = false;
    bool altKey = false;
    bool shiftKey = false;
    int virtualKey = 0;        // Qt::Key_ value (0 = no shortcut)

    QString folderName;        // Optional submenu folder for organization

    /**
     * @brief Convert macro to XML element
     * @param doc The XML document
     * @return QDomElement representing this macro
     */
    QDomElement toXml(QDomDocument& doc) const;

    /**
     * @brief Create macro from XML element
     * @param element The XML element to parse
     * @return Macro parsed from XML
     */
    static Macro fromXml(const QDomElement& element);

    /**
     * @brief Check if macro has a keyboard shortcut assigned
     * @return true if virtualKey is set
     */
    bool hasShortcut() const { return virtualKey != 0; }

    /**
     * @brief Get human-readable shortcut string
     * @return String like "Ctrl+Alt+S" or empty if no shortcut
     */
    QString shortcutString() const;

    /**
     * @brief Get Qt key sequence for this macro's shortcut
     * @return QKeySequence representing the shortcut
     */
    QKeySequence keySequence() const;

    /**
     * @brief Check if macro is valid (has name and actions)
     * @return true if macro can be saved/executed
     */
    bool isValid() const;

    /**
     * @brief Get count of actions in this macro
     * @return Number of actions
     */
    int actionCount() const { return actions.size(); }

    /**
     * @brief Update the modified timestamp to now
     */
    void touch();
};

} // namespace NotepadPlusPlus
