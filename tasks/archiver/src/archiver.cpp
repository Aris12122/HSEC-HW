#include <fstream>
//#include "init.h"
#include "CLA/cla_parser.h"
#include "Exceptions/exceptions.h"
#include "iostream"

int main(int argc, char** argv) {
    try {
        // обработка аргументов
        CLAParser args("A program for compressing multiple files and decompressing a single file using the Huffman algorithm.\n"
                       "Performed by Mikhail Tropin (Aris)");
        std::vector<std::string> input_files;
        std::string output_file;
        std::string archive_file;

        args.AddMultipleArgument('c', "compress", "archive_name file1 [file2 ...]",
                               "compress files file1 [file2..] to file archive_name",
                               &output_file, &input_files);
        args.AddUniqueArgument('d', "decompress", "archive_name", "decompress file archive_name", &archive_file);
        args.AddFlag('h', "help", "Prints help message with usage");

        args.Parse(argc, argv);

        if (args.ToPerform("help")) {
            //            if (args.ToPerform("compress")) {
            //                std::cerr << "Expected unique argument, but -h and -c found" << std::endl;
            //                throw InvalidArguments();
            //            }
            //            if (args.ToPerform("decompress")) {
            //                std::cerr << "Expected unique argument, but -h and -d found" << std::endl;
            //                throw InvalidArguments();
            //            }
            args.PrintHelpMessages(std::cout);
            //        } else if (args.ToPerform("compress")) {
            //            if (args.ToPerform("decompress")) {
            //                std::cerr << "Expected unique argument, but -c and -d found" << std::endl;
            //                throw InvalidArguments();
            //            }
            //            if (input_files.empty()) {
            //                std::cerr << "Expected at least one input_file for compression but zero found" << std::endl; throw InvalidArguments();
            //            }
            //            std::ofstream output = std::ofstream(output_file);
            //            if (!output) {
            //                std::cerr << "Cannot open output_file : " << output_file << std::endl;
            //                throw IOSException();
            //            }
            //            Writer writer(output);
            //
            //            for (size_t i = 0; i < input_files.size(); ++i) {
            //                std::string input_file = input_files[i];
            //
            //                std::ifstream input(input_file.c_str(), std::ios::binary);
            //                if (!input) {
            //                    std::cerr << "Cannot open input_file : " << input_file << std::endl;
            //                    throw IOSException();
            //                }
            //
            //                Encoder encoder;
            //
            //                {
            //                    encoder.Add(TransformFileName(input_file));
            //                    encoder.Add(FILENAME_END);
            //                    Reader reader(input);
            //                    encoder.Add(reader);
            //                    if (i + 1 == input_files.size()) {
            //                        encoder.Add(ARCHIVE_END);
            //                    } else {
            //                        encoder.Add(TransformFileName(input_files[i+1]));
            //                    }
            //                }
            //
            //                encoder.Encode();
            //
            //                {
            //                    encoder.PrintTrieData(writer);
            //                    encoder.PrintEncoded(TransformFileName(input_file), writer);
            //                    encoder.PrintEncoded(FILENAME_END, writer);
            //
            //                    input.seekg(0);
            //                    Reader reader(input);
            //                    encoder.PrintEncoded(reader, writer);
            //
            //                    if (i + 1 == input_files.size()) {
            //                        encoder.PrintEncoded(ARCHIVE_END, writer);
            //                    } else {
            //                        encoder.PrintEncoded(ONE_MORE_FILE, writer);
            //                    }
            //                }
            //            }
            //        } else if (args.ToPerform("decompress")) {
            //
            //        } else {
            //            std::cerr << "Expected exactly one argument but zero found" << std::endl;
            //            throw InvalidArguments();
            //        }
        }
    } catch (InvalidArguments e) {
        std::cerr << "Invalid Argument Exception occurred" << std::endl;
        return 111;
    } catch (IllegalStateException e) {
        std::cerr << "Illegal State Exception occurred" << std::endl;
        return 111;
    } catch (std::exception e) {
        std::cerr << "Unknown exception\n" << e.what() << std::endl;
        return 111;
    }
    return 0;
}
