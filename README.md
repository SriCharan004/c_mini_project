# Flight Management System

This project implements a simple Flight Booking System using C programming language. It allows users to register, book flights, check flight status, cancel tickets, and admin can manage flights and users.

## Access

There are two accesses:
- Password-protected admin access
- User access

## Admin Access

Admin has the key control and has the following abilities:

### Admin Abilities

- Insert flight records
- Modify flight records
- Delete flight records
- Display flight records
- View registered users
- View users who have booked tickets and their details

## User Access

The user has the following abilities:

### User Abilities

- See the upcoming flight journeys
- Register before booking tickets
- Book tickets
- Cancel tickets
- Add the amount to their balance
- Know the status of the flight they have booked
- Check their balance

## Utility Functions

There are several utility functions written for consistency in logic and work. Their duties include:

- Increase the flight's capacity
- Check if a registration number is already registered
- Verify the existence of a flight number
- Retrieve a user by name
- Retrieve a user by number
- Add balance to a user's account
- Check a user's balance
- Count occurrences of a name with a flight number
- Deduct balance from a user's account
- Increase the capacity of a flight
- Add a refund for canceled flights
- Delete booked users for a specified flight number

## Structures

#### Schedule Structure
- Stores time and date information including hours, minutes, day, month, and year.

#### Flight Structure
- Represents a flight with attributes such as flight number, maximum capacity, current capacity, fare, schedule, origin, and destination.

#### User Structure
- Defines user details including name, unique number, password, and balance.

#### Booked User Structure
- Holds information about booked users including username, unique number, age, passenger name, and flight number.

## Approach

File Handling
