# 💰 BudgetBuddy

**BudgetBuddy** is a desktop financial management app built with **C++**, **Qt Widgets**, and **SQLite**. It helps users manage money by tracking income and expenses, setting monthly goals, and visualizing spending with clear charts.

---

## 🚀 Features

### 🔐 User Authentication
- **Login Page** — Log in securely with username and password.
- **Signup Page** — Register as a new user with strong password rules.
- **Forgot Password** — Reset password if forgotten, by username.

### 🏠 Home Page
- Central dashboard with navigation:
  - Add or View Transactions
  - Set Monthly Goals
  - Analyze Report
  - Profile & Logout

### 💸 Transactions Page
- Add income or expense entries with:
  - Date
  - Category
  - Type (Income/Expense)
  - Amount
  - Remarks
- View full list of transactions **plus monthly goals** together.
- Filter by **type**, **category**, and **date range**.

### 🎯 Monthly Goals
- Set spending targets for each month.
- Stored in the `monthly_goals` table.
- Tracks progress when adding expenses.

### 📊 Analyze Report
- Select **month & year** to see:
  - Total Income
  - Total Expenses
  - Total Monthly Goal
  - Remaining Budget
  - Pie Chart of Expenses by Category
- Automatic **red warning** if spending exceeds goals.
- Powered by **QtCharts**.

---

## 🛠️ Tech Stack

| Component    | Technology       |
|--------------|------------------|
| Language     | C++              |
| UI Framework | Qt 5 Widgets     |
| Database     | SQLite           |
| Charts       | Qt Charts Module |
| Build Tool   | CMake            |

---

## 🗃️ Database Schema

### `users`
| Field    | Type                |
|----------|---------------------|
| id       | INTEGER PRIMARY KEY |
| username | TEXT                |
| password | TEXT                |

### `transactions`
| Field    | Type                |
|----------|---------------------|
| id       | INTEGER PRIMARY KEY |
| user_id  | INTEGER             |
| date     | TEXT                |
| category | TEXT                |
| type     | TEXT (Income/Expense) |
| amount   | REAL                |
| remarks  | TEXT                |

### `monthly_goals`
| Field    | Type                |
|----------|---------------------|
| id       | INTEGER PRIMARY KEY |
| user_id  | INTEGER             |
| month    | INTEGER             |
| year     | INTEGER             |
| amount   | REAL                |

---

## 📁 Project Structure

```
BudgetBuddy/
├── main.cpp
├── login.cpp/h
├── signup.cpp/h
├── homepage.cpp/h
├── transactions.cpp/h
├── monthlygoals.cpp/h
├── analyzereport.cpp/h
├── forgotpassword.cpp/h
├── databasemanager.cpp/h
├── *.ui (Qt Designer UI files)
└── BudgetBuddy.db
```

---

## 🏗️ How to Build

1. **Install Qt 5** (Qt Creator, QtCharts).
2. Clone this repository:
   ```bash
   git clone https://github.com/aasishhumagain/BudgetBuddy_test
   cd BudgetBuddy_test
   ```
3. Open in Qt Creator **or** build manually:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ./BudgetBuddy_test
   ```

---

## 📸 Screens Included

| Screen           | Description                        |
|------------------|------------------------------------|
| Login            | Username + password login          |
| Signup           | New user registration with rules   |
| Forgot Password  | Reset password using username      |
| Home Page        | Navigation hub                     |
| Transactions     | Add/view with filters & goals      |
| Monthly Goals    | Create monthly spending targets    |
| Analyze Report   | Filtered pie chart & goal check    |


# Built by BudgetBuddy Team ❣️