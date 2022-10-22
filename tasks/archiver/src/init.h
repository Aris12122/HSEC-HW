//
// Created by aris on 10/20/22.
//
#pragma once

#include <iostream>

#include "CLA/cla_parser.h"
#include "Symbol/symbol.h"
#include "IO/reader.h"
#include "IO/writer.h"
#include "Huffman/huffman.h"
#include "Huffman/encoder.h"
#include "Huffman/decoder.h"
#include "Exceptions/exceptions.h"


static const size_t WORD_LEN = 8u;
static const Symbol FILENAME_END = Symbol(256u);
static const Symbol ONE_MORE_FILE = Symbol(257u);
static const Symbol ARCHIVE_END = Symbol(258u);

