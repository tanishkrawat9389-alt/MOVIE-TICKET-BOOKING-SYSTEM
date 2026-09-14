# Movie Ticket Booking System — TCS-504 Assignment 1

A menu-driven C++ console program for a single cinema, implementing the assignment requirements F1–F8.

## Features
- List currently playing movies
- List shows by movie (screen + start time)
- Display AVAILABLE / BOOKED seat layout
- Book one or more seats; reject any already-booked/invalid seat
- Seat pricing: SILVER ₹150, GOLD ₹250, PLATINUM ₹400
- Payment by UPI, Card or Cash
- Failed payment does not confirm a booking
- Print ticket with booking ID, movie, screen, time, seats and amount
- Cancel a booking and release its seats

## Build and run

Use a C++17 compiler:

```bash
g++ -std=c++17 main.cpp -o movie_booking
./movie_booking
```

The project follows the assignment's no-header-file approach: source files are composed through `#include` directives. `#pragma once` is used where the same implementation file can be reached through more than one dependency path.

## File structure

`01_Movie.cpp`, `02_Seat.cpp`, `03_Screen.cpp`, `04_Cinema.cpp`, `05_Show.cpp`, `06_ShowSeat.cpp`, `07_Customer.cpp`, `08_Booking.cpp`, `09_Payment.cpp`, `10_PaymentTypes.cpp`, `11_PriceCalculator.cpp`, `12_TicketPrinter.cpp`, `13_BookingService.cpp`, `main.cpp`.

## OOP and design
- Encapsulation: private booking amount/status and seat status with controlled methods.
- Abstraction: abstract `Payment` with pure virtual `pay(double)`.
- Inheritance: UPI, Card and Cash payment implementations derive from `Payment`.
- Runtime polymorphism: `Payment` interface invokes the concrete payment implementation.
- Compile-time polymorphism: overloaded `Movie` constructors.
- Static member: `Booking::nextBookingId` generates unique IDs.
- Composition: Cinema→Screen, Screen→Seat, Show→ShowSeat.
- Aggregation: Show→Movie, Booking→ShowSeat.
- Association: Customer→BookingService.

## Failure-path demo
For UPI or Card, entering `fail` as the requested reference deliberately simulates a failed payment. The selected seats remain AVAILABLE and no confirmed ticket is produced.

## SOLID
- **S — Single Responsibility:** pricing is in `PriceCalculator`; printing is in `TicketPrinter`; booking orchestration is in `BookingService`.
- **O — Open/Closed:** a new payment type can derive from `Payment` without changing the payment contract.
- **L — Liskov Substitution:** each payment implementation can be used through `Payment`.
- **D — Dependency Inversion:** `BookingService` uses the abstract `Payment` interface rather than depending on one concrete payment class.

### Deliberately not implemented
Persistent database storage was deliberately not added because the assignment specifies a small single-cinema console program and asks for exactly the listed scope.
