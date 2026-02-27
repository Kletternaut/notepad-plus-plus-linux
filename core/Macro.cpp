#include "Macro.h"
#include <QDebug>

namespace NotepadPlusPlus {

// ============================================================================
// MacroAction Implementation
// ============================================================================

QDomElement MacroAction::toXml(QDomDocument& doc) const
{
    QDomElement element = doc.createElement("Action");
    element.setAttribute("type", type);
    element.setAttribute("message", QString::number(message));
    element.setAttribute("wParam", QString::number(wParam));
    element.setAttribute("lParam", QString::number(lParam));

    // Only add sParam if not empty (matches Notepad++ format)
    if (!sParam.isEmpty()) {
        element.setAttribute("sParam", sParam);
    } else {
        element.setAttribute("sParam", "");
    }

    return element;
}

MacroAction MacroAction::fromXml(const QDomElement& element)
{
    MacroAction action;

    action.type = element.attribute("type", "1").toInt();
    action.message = element.attribute("message", "0").toUInt();
    action.wParam = element.attribute("wParam", "0").toULong();
    action.lParam = element.attribute("lParam", "0").toLong();
    action.sParam = element.attribute("sParam", "");

    return action;
}

bool MacroAction::isValid() const
{
    // Action must have a message ID
    return message != 0;
}

// ============================================================================
// Macro Implementation
// ============================================================================

QDomElement Macro::toXml(QDomDocument& doc) const
{
    QDomElement element = doc.createElement("Macro");

    // Basic attributes
    element.setAttribute("name", name);

    // Keyboard shortcut attributes (Notepad++ format: "yes"/"no")
    element.setAttribute("Ctrl", ctrlKey ? "yes" : "no");
    element.setAttribute("Alt", altKey ? "yes" : "no");
    element.setAttribute("Shift", shiftKey ? "yes" : "no");
    element.setAttribute("Key", virtualKey);

    // Optional folder organization
    if (!folderName.isEmpty()) {
        element.setAttribute("FolderName", folderName);
    }

    // Store metadata as child elements (not in Notepad++ format, but useful)
    if (!description.isEmpty()) {
        QDomElement descElement = doc.createElement("Description");
        descElement.appendChild(doc.createTextNode(description));
        element.appendChild(descElement);
    }

    if (created.isValid()) {
        QDomElement createdElement = doc.createElement("Created");
        createdElement.appendChild(doc.createTextNode(created.toString(Qt::ISODate)));
        element.appendChild(createdElement);
    }

    if (modified.isValid()) {
        QDomElement modifiedElement = doc.createElement("Modified");
        modifiedElement.appendChild(doc.createTextNode(modified.toString(Qt::ISODate)));
        element.appendChild(modifiedElement);
    }

    // Add all actions
    for (const MacroAction& action : actions) {
        element.appendChild(action.toXml(doc));
    }

    return element;
}

Macro Macro::fromXml(const QDomElement& element)
{
    Macro macro;

    // Read basic attributes
    macro.name = element.attribute("name");

    // Read keyboard shortcut (Notepad++ uses "yes"/"no" strings)
    macro.ctrlKey = (element.attribute("Ctrl", "no").toLower() == "yes");
    macro.altKey = (element.attribute("Alt", "no").toLower() == "yes");
    macro.shiftKey = (element.attribute("Shift", "no").toLower() == "yes");
    macro.virtualKey = element.attribute("Key", "0").toInt();

    // Read optional folder
    macro.folderName = element.attribute("FolderName", "");

    // Read metadata child elements
    QDomElement child = element.firstChildElement();
    while (!child.isNull()) {
        if (child.tagName() == "Description") {
            macro.description = child.text();
        } else if (child.tagName() == "Created") {
            macro.created = QDateTime::fromString(child.text(), Qt::ISODate);
        } else if (child.tagName() == "Modified") {
            macro.modified = QDateTime::fromString(child.text(), Qt::ISODate);
        } else if (child.tagName() == "Action") {
            MacroAction action = MacroAction::fromXml(child);
            if (action.isValid()) {
                macro.actions.append(action);
            }
        }

        child = child.nextSiblingElement();
    }

    return macro;
}

QString Macro::shortcutString() const
{
    if (!hasShortcut()) {
        return QString();
    }

    QStringList parts;
    if (ctrlKey) parts << "Ctrl";
    if (altKey) parts << "Alt";
    if (shiftKey) parts << "Shift";

    // Convert virtual key to readable string
    if (virtualKey >= Qt::Key_A && virtualKey <= Qt::Key_Z) {
        // Letter keys
        parts << QChar('A' + (virtualKey - Qt::Key_A));
    } else if (virtualKey >= Qt::Key_0 && virtualKey <= Qt::Key_9) {
        // Number keys
        parts << QChar('0' + (virtualKey - Qt::Key_0));
    } else if (virtualKey >= Qt::Key_F1 && virtualKey <= Qt::Key_F35) {
        // Function keys
        parts << QString("F%1").arg(virtualKey - Qt::Key_F1 + 1);
    } else {
        // Other keys - use Qt's name
        QKeySequence seq(virtualKey);
        parts << seq.toString();
    }

    return parts.join("+");
}

QKeySequence Macro::keySequence() const
{
    if (!hasShortcut()) {
        return QKeySequence();
    }

    int key = virtualKey;

    if (ctrlKey) {
        key |= Qt::CTRL;
    }
    if (altKey) {
        key |= Qt::ALT;
    }
    if (shiftKey) {
        key |= Qt::SHIFT;
    }

    return QKeySequence(key);
}

bool Macro::isValid() const
{
    // Macro must have a name and at least one valid action
    if (name.isEmpty()) {
        return false;
    }

    if (actions.isEmpty()) {
        return false;
    }

    // Check that at least one action is valid
    for (const MacroAction& action : actions) {
        if (action.isValid()) {
            return true;
        }
    }

    return false;
}

void Macro::touch()
{
    modified = QDateTime::currentDateTime();
}

} // namespace NotepadPlusPlus
