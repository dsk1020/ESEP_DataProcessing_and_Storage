# ESEP Data Processing & Storage
This assignment focuses on creating in-memory databases to simulate transactions. My implementation was done in C++.
## Table of Contents
- [Setup](#setup)
- [How To Run](#how-to-run)
- [Testing](#testing)
- [Recommendations for the Assignment](#Recommendations-for-the-Assignment)

## Setup
To run the project it requires a couple of things to be set up.
- g++
- Cmake
- [Google Test](https://github.com/google/googletest)

Instructions on how to set up the tools on [macOS](https://alexanderbussan.medium.com/getting-started-with-google-test-on-os-x-a07eee7ae6dc) (NOT homebrew)

Instructions on how to set up on [Windows](https://stackoverflow.com/questions/531941/how-to-set-up-google-c-testing-framework-gtest-with-visual-studio-2005) (NOT TESTED as all development on macOS)

## How to Run
There are two ways to run this project: running it directly and running unit tests.

### Direct
Running the project will only display the exceptions printed to stdout.
- Clone this repository
- Navigate inside the directory with the Makefile
- Compile the code with `make direct.out`
- Run the program `./direct.out`

### Unit Tests
Unit testing was done using Google Test.
- Set up Google Tests as mentioned before
- Clone this repository
- Navigate inside the directory with the Makefile
- Compile the project with `make`
- Run the unit tests with `./test.out`

## Testing
I have included the test suite I used to test my code. Testing was done using Google Tests for C++. There are 3 test suites: 
- Exceptions - Test that the functions throw exceptions when their supposed to
- Functionality - Tests that the functionality of the database works as intended
- Large Tests - Tests everything in a larger scale. Uses the provided scenario, and other large cases
    
## Recommendations for the Assignment
- One thing I would recommend if giving more clarity on how to handle throwing exceptions. Currently you can either throw and terminate execution, or catch it and print an error message. 
  - For my implementation I choose to print an error message because if there is a bad transaction it should log a message and not execute it rather than terminate and stop execution all together.
- Something I would add to the assignment is have each "key" store a history aff all of its transactions. If this is based the idea of a financial institution moving money between accounts then there should be a record of it. This would require another function to get the history. Also, this may need a different put function to have a sender. Implementing this should be too much more difficult or time-consuming that the current assignment.
- Thinking about the graders this may be a very difficult assignment to grade because of how much variance there will be between each submission. With each submission needing different setup and different ways to run means it would need to be graded manually and functionality cant be automated. It may be helpful to limit to a few very popular languages ex: (Python, Java, C++) and have unit testing for each language. Also, define fro students the submission format so that all submission within a language match.
