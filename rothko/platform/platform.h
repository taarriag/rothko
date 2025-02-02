// Copyright 2019, Cristián Donoso.
// This code has a BSD license. See LICENSE.

#pragma once

#include <string>

namespace rothko {

// The platform is meant to give an interface to OS specific functionality
// in an uniform way. Each platform should compile its own implementation of
// this interface. The implementations are in rothko/arch/*_platform.cc

std::string GetBasePath();
std::string GetCurrentExecutablePath();
std::string GetCurrentExecutableDirectory();

// Amount of nanoseconds since the program started.
uint64_t GetNanoseconds();

}  // namespace rothko
