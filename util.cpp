#pragma once

#define free( ptr ) delete ptr; ptr = nullptr;