'''
#!/usr/bin/env python
'''
__author__ = "Anastasis Keliris"
__licence__ = "MIT"

# Imports
from subprocess import call
import os, sys
from optparse import OptionParser

def main(argv):
    '''
    Main function: Parses command line arguments and updates checksum
    '''

    parser = OptionParser()
    parser.add_option("-i", "--input", dest="inputfile",
                      help="Input file for checksum verification", default = None)
    parser.add_option("-o", "--output", dest="outputfile",
                      help="Output file with valid checksum", default = None)
    parser.add_option("-r", action="store_true", dest="remout",
                      help="Delete output file")
       
    # Get command line arguments                  
    (options, args) = parser.parse_args()
    
    # Check arguments
    if not options.inputfile:
            parser.print_help()
            sys.exit(1)
    
    infile = options.inputfile
    if options.remout:
        del_output = True
    else:
        del_output = False
    if not options.outputfile:
        outfile = os.path.splitext(infile)[0] + "_vld" + os.path.splitext(infile)[1]
    else:
        outfile = options.outputfile


    # Variable initialization
    linecount = 0
    passcount = 0
    missmatch = []

    # Open files
    f_in = open(infile,'r')
    f_out = open(outfile,'w')

    # Find checksum for every non-empty line in input file
    for line in f_in:
        linecount += 1
        chksum = 0
        line_data = line.rstrip()
        # Check if data has correct length
        if len(line_data) % 2 == 0 and line_data:
            call(["rm", outfile])
            raise ValueError
        # Calculate checksum
        if line_data:
            line_data = [int(line_data[x:x+2],16) for x in range(1,len(line_data),2)]
            chksum = ((sum(line_data[:-1]) ^ 0xff)+1 ) & 0xff
            if line_data[-1] == chksum:
                passcount += 1
            else:
                missmatch.append(linecount)
                line = line.rstrip()[:-2] + str(hex(chksum)[2:]).upper() + "\n"
            f_out.write(line)

    # Close files
    f_in.close()
    f_out.close()

    if del_output:
        call(["rm", outfile])
    # Print information
    if missmatch:
        print("Total number of lines: {}".format(linecount))
        print("Number of lines with checksum missmatch: {}".format(linecount - passcount))
        print("File diff for visual inspection:")
        call(["diff", infile, outfile])
    else:
        print("All {} lines have correct checksum".format(linecount))

# Call main with command line arguments
if __name__ == "__main__":
    main(sys.argv[1:])