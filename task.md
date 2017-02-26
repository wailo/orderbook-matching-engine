Programming Challenge
==============================

# Introduction
This test is designed to assess:
* how do you analyze a problem 
* define the perimeter you are going to address
* provide a precise description of your solution Your design and coding skills Your engineering/craftsmanship principles

# Overview
The objective is to develop a matching engine for limit orders (buys and sells) for an unspecified set of listed instruments. The deliverable should include the set of unit tests written using boost unit test framework, and no other executable is required besides the one created by the unit test framework.

# Tasks
The matching engine is the core component to build, providing the following APIs:
    * An order management API, used to send orders, receive order updates and executions
    * A market data API, used by a client (the unit test) to receive the order book as well as public trades (report of execution where client identification has been removed)
Contract details can be assumed to be specified somewhere else and contracts may be treated as uniquely identified entities for which orders are sent and live data is subscribed to: a data structxure with a unique identifier of your choice.
The matching engine receives order requests from the clients, keeps track of all active orders in the market for each product and matches the
orders based on an algorithm of your choice.
When the matching engine receives an order, it should check if it can be matched with orders that it already has for the given contract:
    * if it doesn't cross the price in the other side, then it should be kept in the list of active orders and published through the market data API.
    * if it crosses the other side fully or partially, then it should generate as many execution data objects as necessary, depending on the volume matched against the order/s in the opposite side, notifying them to the parties involved (orders' owners). This should trigger updates on the state of the orders for those parties too, as well as updates via the market data API.

# Example:
Client A sends 3 buy orders for product 1. The engine confirms each order to client A as being active in the market and, also, it sends update
notifications (as changes happen) to all clients that are connected to the market data API:
Orders:
Order 1 Buy 100@12.30
Order 2 Buy 25@12:15
Order 3 Buy 10@12.20
The book will look like this after the last order was sent:
B.Vol B.Price A.Price A.Vol
100 12.30
10 12.20
25 12.15
Client B sends a sell order (order 4) (115@12.17). This should trigger 2 executions for each client:
For client A:
Buy 100@12.30
Buy 10@12.20
For client B:
Sell 100@12.30
Sell 10@12.20
It should notify both clients of the new state of their orders:
For client A:
Order 1 filled
Order 2 filled
For client B:
Order 4 Partially filled (active volume 5@12.17)
The final book looks like this:
B.Vol B.Price A.Price A.Vol
25 12.15 12.17 5
Clients using the market data API receive updates for the book (once the matching for a given order is completed) as well as the 3 public trades.

# Project report
 * Formal and well formatted document (pdf, word, etc.) explaining your solution to the challenge:
 * Design and implementation choices and the rationale behind them.
 * Schematics are welcome, as long as they do not replace clear sentences.

# Technical requirements
 * C++14
 * Boost 1.60 
 * Mac (Clang 3.7), as a package including
 *  sources and CMake build files.
 * External libraries are allowed, as long as they are embedded within your solution and do not require installation steps.
 * OS level primitives such as file or socket access are permitted, either used directly or through external libraries.
