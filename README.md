# CoreRecruit

A robust C++ application for managing job applicants, built with a multi-layer architecture and PostgreSQL database integration. CoreRecruit streamlines the recruitment process with CRUD operations, position-based search, and comprehensive status tracking capabilities.

## 📋 Overview

CoreRecruit is a command-line inventory management system designed for HR departments and recruitment teams. It provides an efficient way to track job applicants throughout the hiring process, from initial application to final decision.

## ✨ Features

- **Applicant Management**: Add, view, update, and delete applicant records
- **Position-Based Search**: Quickly find applicants by job position
- **Status Tracking**: Monitor applicant progress through the recruitment pipeline
  - Pending
  - Interviewed
  - Hired
  - Rejected
- **Database Persistence**: Secure data storage using PostgreSQL
- **Clean Architecture**: Multi-layer design (Controller → Service → DAO → Database)
- **Input Validation**: Ensures data integrity with built-in validation
- **Detailed Reporting**: View comprehensive applicant information

## 🏗️ Architecture

CoreRecruit follows a layered MVC-style architecture:

```
┌─────────────────────┐
│  ApplicantController │  ← User Interface Layer
└──────────┬──────────┘
           │
┌──────────▼──────────┐
│  ApplicantService   │  ← Business Logic Layer
└──────────┬──────────┘
           │
┌──────────▼──────────┐
│   ApplicantDAO      │  ← Data Access Layer
└──────────┬──────────┘
           │
┌──────────▼──────────┐
│ DatabaseConnection  │  ← Database Layer
└──────────┬──────────┘
           │
      PostgreSQL
```

### Components

- **Applicant**: Entity class representing applicant data
- **ApplicantController**: Handles user input/output and menu navigation
- **ApplicantService**: Business logic and validation
- **ApplicantDAO**: Database operations (CRUD)
- **DatabaseConnection**: PostgreSQL connection management

## 🛠️ Tech Stack

- **Language**: C++ (C++11 or higher)
- **Database**: PostgreSQL
- **Database Driver**: libpq (PostgreSQL C library)
- **Build System**: Make/CMake (or your preferred build tool)

## 📦 Prerequisites

Before you begin, ensure you have the following installed:

### Required Software
- **C++ Compiler** (GCC 7+ or Clang 5+)
- **PostgreSQL** (v12 or higher)
- **libpq-dev** (PostgreSQL development library)
- **Make** or **CMake** (for building)

### Installation Commands

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install g++ postgresql postgresql-contrib libpq-dev
```

#### macOS
```bash
brew install postgresql libpq
```

#### Windows
- Install [MinGW-w64](https://www.mingw-w64.org/)
- Install [PostgreSQL](https://www.postgresql.org/download/windows/)

## 🚀 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/Manmohit-24-Singh/CoreRecruit.git
cd CoreRecruit
```

### 2. Set Up PostgreSQL Database

```bash
# Start PostgreSQL service
sudo service postgresql start  # Linux
brew services start postgresql  # macOS

# Create database and user
sudo -u postgres psql

# In PostgreSQL prompt:
CREATE DATABASE corerecruit;
CREATE USER corerecruit_user WITH PASSWORD 'your_password';
GRANT ALL PRIVILEGES ON DATABASE corerecruit TO corerecruit_user;
\q
```

### 3. Configure Database Connection

Update the database credentials in `main.cpp`:

```cpp
auto dbConn = std::make_shared<DatabaseConnection>(
    "localhost",           // host
    "5432",               // port
    "corerecruit",        // database name
    "corerecruit_user",   // username
    "your_password"       // password
);
```

### 4. Compile the Application

#### Using g++
```bash
g++ -std=c++11 -o corerecruit \
    main.cpp \
    Applicant.cpp \
    ApplicantController.cpp \
    ApplicantDAO.cpp \
    ApplicantService.cpp \
    DatabaseConnection.cpp \
    -lpq
```

#### Using CMake (if CMakeLists.txt exists)
```bash
mkdir build
cd build
cmake ..
make
```

## 🎯 Usage

### Running the Application

```bash
./corerecruit
```

### Menu Options

```
=== Job Applicant Inventory System ===
1. Add Applicant
2. View All Applicants
3. Search by Position
4. Update Applicant Status
5. Delete Applicant
6. View Applicant Details
7. Exit
```

### Example Workflow

1. **Add New Applicant**
   - Enter name, email, phone, position, and years of experience
   - System automatically sets status to "pending"

2. **Search by Position**
   - Find all applicants for a specific job role
   - Case-insensitive partial matching

3. **Update Status**
   - Change applicant status as they progress through hiring
   - Valid statuses: pending, interviewed, hired, rejected

4. **View Details**
   - Display comprehensive information for a specific applicant

## 📂 Project Structure

```
CoreRecruit/
├── Applicant.h                 # Applicant entity header
├── Applicant.cpp               # Applicant entity implementation
├── ApplicantController.h       # Controller header
├── ApplicantController.cpp     # Controller implementation
├── ApplicantService.h          # Service layer header
├── ApplicantService.cpp        # Service layer implementation
├── ApplicantDAO.h              # Data access layer header
├── ApplicantDAO.cpp            # Data access layer implementation
├── DatabaseConnection.h        # Database connection header
├── DatabaseConnection.cpp      # Database connection implementation
├── main.cpp                    # Application entry point
└── README.md                   # Project documentation
```

## 🗄️ Database Schema

```sql
CREATE TABLE applicants (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    position VARCHAR(100),
    experience_years INT,
    status VARCHAR(20) DEFAULT 'pending'
);
```

### Fields
- **id**: Auto-incrementing primary key
- **name**: Applicant's full name
- **email**: Unique email address
- **phone**: Contact phone number
- **position**: Applied job position
- **experience_years**: Years of relevant experience
- **status**: Current application status

## 🔧 Configuration

### Database Connection Parameters

Modify in `main.cpp` or create a config file:
- **Host**: Database server address (default: localhost)
- **Port**: PostgreSQL port (default: 5432)
- **Database**: Database name
- **User**: Database username
- **Password**: Database password

### Customization Options

- Add new applicant fields in `Applicant` class
- Extend status options in `ApplicantService`
- Implement additional search filters
- Add export/import functionality

## 🐛 Troubleshooting

### Common Issues

**Connection Failed**
```
Error: Database connection failed
```
**Solution**: Verify PostgreSQL is running and credentials are correct

**Compilation Errors**
```
fatal error: libpq-fe.h: No such file or directory
```
**Solution**: Install libpq-dev library
```bash
sudo apt-get install libpq-dev
```

**Permission Denied**
```
FATAL: role "user" does not exist
```
**Solution**: Create the PostgreSQL user with proper permissions

## 🔒 Security Considerations

- **SQL Injection**: Current implementation uses string concatenation. Consider using prepared statements for production
- **Password Storage**: Store database credentials securely (environment variables or config files with restricted permissions)
- **Input Sanitization**: Validate and sanitize all user inputs
- **Connection Security**: Use SSL/TLS for database connections in production

## 🚀 Future Enhancements

- [ ] Add resume file upload support
- [ ] Implement interview scheduling
- [ ] Email notification system
- [ ] Export reports (CSV, PDF)
- [ ] Multi-user authentication
- [ ] Web-based GUI
- [ ] REST API integration
- [ ] Advanced search filters (experience range, date added)

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Coding Standards
- Follow C++ Core Guidelines
- Use meaningful variable names
- Comment complex logic
- Write unit tests for new features

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

**Manmohit Singh**
- GitHub: [@Manmohit-24-Singh](https://github.com/Manmohit-24-Singh)
- Project Link: [https://github.com/Manmohit-24-Singh/CoreRecruit](https://github.com/Manmohit-24-Singh/CoreRecruit)


## 📞 Support

For support, issues, or feature requests:
- Open an issue on [GitHub Issues](https://github.com/Manmohit-24-Singh/CoreRecruit/issues)
- Contact the maintainer through GitHub

---
