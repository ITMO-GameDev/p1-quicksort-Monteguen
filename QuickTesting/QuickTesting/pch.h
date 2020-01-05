//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

template <typename T>
class Temp2 {
public:
	Temp2(T *a1, T *b1, bool (*func)(T a,T b) );
};