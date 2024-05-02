# Reason -> Who, Why, How, What

- Write In Memory Testable DB Project
1. WHO: Developers (Performance View)
    1. WHY: Must be swappable for tests (Db Concepts)
        1. HOW: SQL input is the same as SQL server
        2. HOW: Can support multiple versions of SQL Server DB/Azure
    2. WHY: Performance is not a priority/important as its in memory
    3. WHY: Must be usable in dotnet projects
        1. HOW: Adapters in code available
2. WHO: Me
    1. WHY: Learn SqlServer Database Concepts (swap for tests)
        1. Learn about the underlying types I need to support
        2. How the database takes input with various queries
        3. What are the typical queries?
        4. How to store/retrieve/construct the database
        5. Look at DB from an input/black box perspective

# Why?

Learning new concepts and the underlying technology layer.

# Description

Write a SQL Lite database engine to explore database concepts, TDD, and C programming.

# Requirements

1. CREATE TABLE STATEMENT
2. INSERT INTO STATEMENT
3. SELECT STATEMENT
