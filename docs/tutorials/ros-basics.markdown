---
layout: default
title: ROS Basics
parent: Tutorials
nav_order: 2
---

## ROS Basics

Let us understand some fundamentals behind ROS! We will brush over the following topics:

1. Nodes
2. Messages
3. Topics
4. Master
5. Services
6. Publisher & Subscriber
7. Bags
8. Parameter Server

### Nodes

Nodes are the primary unit of abstraction in ROS. It basically is an executable program that implements a certain functionality. A robotic process or a system is usually comprised of several such nodes working in parallel and communicating with each other via exchanging messages over a toppic.

### Messages

How do Nodes communicate is via Messages. A Message in ROS is just a basic data structure composed of basic data types such as integer, floating point, boolean. A simple message structure looke like this:

```
fieldtype1 fieldname1
fieldtype2 fieldname2
```

where fieldtype1 represents any of the valid basic data type and the fieldname1 represents the name of this field

```
int speed
float32 temperature
```

Here is a summary of the available data types mapping to C++ (not exhaustive):

| ROS DataType   | Serialization               | C++ Data Type |
|:---------------|:----------------------------|:--------------|
| bool           | unsigned 8 bit int          | uint8         |
| int8           | signed 8 bit int            | int8          |
| uint8          | unsigned 8 bit int          | uint8         |
| int16          | signed 16 bit int           | int16         |
| uint32         | unsigned 32 bit int         | uint32        |
| int32          | signed 32 bit int           | int32         |
| string         | ascii string                | std::string   |
| time           | unsigned 32 bit ints (secs) | ros::Time     |


### Topics

### Master

