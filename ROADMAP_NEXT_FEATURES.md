# Notepad++ Linux - Next Features Roadmap

## Current Status: 75% Feature Parity ✅

**Just Completed:** Macro System (100% functional)
**Next Target:** 85-90% Feature Parity

---

## Priority 1: Quick Wins (High Impact, Low Effort)

### 1. **Backup/Auto-Save System** ⭐ RECOMMENDED NEXT
**Effort:** 2-3 hours | **Impact:** High | **Framework:** Already exists

**What's Missing:**
- Framework exists in Application.cpp (line 267)
- Settings UI exists in PreferencesDialog
- Just need to implement the backup logic

**Implementation:**
```cpp
// core/BackupManager.h/cpp (NEW)
- Auto-save timer integration
- Backup file creation (.bak files)
- Periodic backup (configurable interval)
- Restore from backup on crash
- Backup directory management
```

**Benefits:**
- Prevents data loss
- Users expect this in a modern editor
- Quick to implement (~200 lines)
- High user satisfaction

---

### 2. **Settings Import/Export** ⭐
**Effort:** 1-2 hours | **Impact:** Medium | **Framework:** Stubbed in PreferencesDialog

**What's Missing:**
- Export settings to file (PreferencesDialog.cpp:717)
- Import settings from file (PreferencesDialog.cpp:705)
- Just JSON/XML serialization of ConfigManager

**Implementation:**
```cpp
// ui/PreferencesDialog.cpp modifications
- exportSettings() - Save all ConfigManager settings to file
- importSettings() - Load settings from file
- File format: JSON or INI
```

**Benefits:**
- Easy to share configurations
- Quick setup on new machines
- Backup user preferences

---

### 3. **Status Bar Enhancements**
**Effort:** 1 hour | **Impact:** Medium | **Framework:** Partial

**What's Missing:**
- Line/column updates (MainWindow_impl.cpp:849)
- Encoding display updates
- File size, selection length

**Implementation:**
- Connect to EditorWidget::cursorPositionChanged
- Update status bar labels on changes
- Show selection character count

---

## Priority 2: High-Value Features (Medium Effort)

### 4. **Bookmarks System** ⭐⭐ HIGHLY RECOMMENDED
**Effort:** 4-6 hours | **Impact:** High | **Complexity:** Medium

**What to Implement:**
```cpp
core/BookmarkManager.h/cpp (NEW ~300 lines)
- Toggle bookmark (Ctrl+F2)
- Next/Previous bookmark (F2/Shift+F2)
- Clear all bookmarks
- Bookmark list panel
- Persist bookmarks per file
```

**QScintilla Support:**
- Built-in marker API (markerAdd, markerDelete)
- Visual indicators in margin
- Easy to integrate

**Benefits:**
- Essential for code navigation
- Quick jumps in large files
- Expected by developers

---

### 5. **Split View Editing** ⭐⭐
**Effort:** 6-8 hours | **Impact:** Very High | **Complexity:** Medium-High

**What to Implement:**
```cpp
core/SplitView.h/cpp (NEW ~400 lines)
- Horizontal split (Ctrl+H)
- Vertical split (Ctrl+V)
- QSplitter widget integration
- Synchronized scrolling option
- Independent cursors
```

**Benefits:**
- Compare code side-by-side
- Edit different parts of same file
- Mentioned in v1.1 roadmap
- Major productivity boost

---

### 6. **Function List Panel** ⭐⭐
**Effort:** 8-10 hours | **Impact:** High | **Complexity:** High

**What to Implement:**
```cpp
ui/FunctionListPanel.h/cpp (NEW ~500 lines)
- Parse file for functions/classes
- Tree view of code structure
- Click to navigate
- Search/filter functions
- Language-specific parsers
```

**Challenges:**
- Need parsers for each language
- Or use ctags/LSP integration
- Complex but very valuable

---

## Priority 3: Advanced Features (High Effort)

### 7. **Plugin System** ⭐⭐⭐ MAJOR UNDERTAKING
**Effort:** 20-30 hours | **Impact:** Very High | **Complexity:** Very High

**Status:**
- Framework exists (Application.cpp:239-249)
- Menu structure ready
- Preferences UI ready
- NO actual plugin loading

**What to Implement:**
```cpp
core/PluginManager.h/cpp (NEW ~800 lines)
core/PluginInterface.h (NEW ~200 lines)
- Plugin discovery (.so files)
- Plugin API definition
- dlopen/dlsym loading
- Plugin lifecycle (init/shutdown)
- Menu integration
- Event system
```

**Benefits:**
- Extensibility (like VSCode extensions)
- Community contributions
- Major differentiator
- v1.1+ feature

**Note:** This is a multi-day project, save for later.

---

### 8. **File Browser/Project Panel**
**Effort:** 10-12 hours | **Impact:** High | **Complexity:** Medium-High

**What to Implement:**
```cpp
ui/FileBrowserPanel.h/cpp (NEW ~600 lines)
- Directory tree view
- File system watcher
- Drag-and-drop to open
- Context menu (rename, delete, new)
- Filter by file type
```

**Benefits:**
- IDE-like experience
- Project management
- Quick file access

---

## Priority 4: Modern Editor Features

### 9. **Multi-Cursor Editing**
**Effort:** 6-8 hours | **Impact:** Medium | **Complexity:** High

**QScintilla Support:**
- SCI_ADDSELECTION, SCI_SETSELECTION
- Multiple selection API exists
- Need UI integration

**Benefits:**
- Modern editor expectation
- Powerful editing capability
- Competitive with VSCode/Sublime

---

### 10. **Column/Block Selection**
**Effort:** 2-3 hours | **Impact:** Medium | **Complexity:** Low

**QScintilla Support:**
- SCI_SETRECTANGULARSELECTIONANCHOR
- Alt+Drag or Alt+Shift+Arrow keys
- Already supported by Scintilla

**Implementation:**
- Add keyboard shortcuts
- Enable rectangular selection mode
- Visual feedback

---

## Recommended Implementation Order

### Phase 1: Polish & Stability (Week 1)
1. ✅ **Backup/Auto-Save System** (2-3 hours)
2. ✅ **Settings Import/Export** (1-2 hours)
3. ✅ **Status Bar Enhancements** (1 hour)
4. ✅ **Column/Block Selection** (2-3 hours)

**Result:** 80% feature parity, stable & polished

---

### Phase 2: Power User Features (Week 2)
5. ✅ **Bookmarks System** (4-6 hours)
6. ✅ **Split View Editing** (6-8 hours)

**Result:** 85% feature parity, major productivity boost

---

### Phase 3: Advanced Features (Week 3-4)
7. ✅ **Function List Panel** (8-10 hours)
8. ✅ **File Browser Panel** (10-12 hours)
9. ✅ **Multi-Cursor Editing** (6-8 hours)

**Result:** 90% feature parity, competitive with modern editors

---

### Phase 4: Extensibility (Future)
10. 🔮 **Plugin System** (20-30 hours)

**Result:** 95%+ feature parity, fully extensible

---

## My Recommendation: Start with Phase 1

**Best Next Feature:** 🎯 **Backup/Auto-Save System**

**Why?**
1. ✅ Framework already exists
2. ✅ Quick to implement (2-3 hours)
3. ✅ High user value (data protection)
4. ✅ Expected in modern editors
5. ✅ Easy win after macro system

**After that:**
- Settings Import/Export (1-2 hours)
- Status Bar (1 hour)
- Column Selection (2-3 hours)

**Total for Phase 1:** ~6-9 hours = 80% feature parity

---

## Feature Comparison

| Feature | Notepad++ Windows | Linux Port (Current) | After Phase 1 | After Phase 2 | After Phase 3 |
|---------|-------------------|---------------------|---------------|---------------|---------------|
| Macro System | ✅ | ✅ | ✅ | ✅ | ✅ |
| Backup/Auto-Save | ✅ | ❌ | ✅ | ✅ | ✅ |
| Bookmarks | ✅ | ❌ | ❌ | ✅ | ✅ |
| Split View | ✅ | ❌ | ❌ | ✅ | ✅ |
| Function List | ✅ | ❌ | ❌ | ❌ | ✅ |
| File Browser | ✅ | ❌ | ❌ | ❌ | ✅ |
| Multi-Cursor | ❌ | ❌ | ❌ | ❌ | ✅ |
| Plugin System | ✅ | ❌ | ❌ | ❌ | 🔮 |
| Settings Export | ✅ | ❌ | ✅ | ✅ | ✅ |
| Column Selection | ✅ | ❌ | ✅ | ✅ | ✅ |
| Status Bar Info | ✅ | ⚠️ | ✅ | ✅ | ✅ |

---

## Quick Reference: Complexity vs Impact

```
High Impact, Low Effort (DO FIRST):
├─ Backup/Auto-Save ⭐⭐⭐
├─ Settings Import/Export ⭐⭐
└─ Column Selection ⭐⭐

High Impact, Medium Effort:
├─ Bookmarks ⭐⭐⭐
├─ Split View ⭐⭐⭐
└─ Function List ⭐⭐

High Impact, High Effort (LATER):
├─ File Browser ⭐⭐
├─ Multi-Cursor ⭐⭐
└─ Plugin System ⭐⭐⭐ (Major)

Low Impact:
└─ Status Bar enhancements
```

---

## What Would You Like to Tackle Next?

**Option A: Quick Wins (Recommended)** 🎯
- Backup/Auto-Save System (2-3 hours)
- Get to 80% parity fast

**Option B: Power User Feature**
- Bookmarks System (4-6 hours)
- Major navigation improvement

**Option C: Visual Impact**
- Split View Editing (6-8 hours)
- Impressive demo feature

**Option D: Major Undertaking**
- Plugin System (20-30 hours)
- Long-term investment

Let me know which direction you want to go! 🚀
