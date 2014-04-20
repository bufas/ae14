def percentage(num_line, den_line):
    num_parts = num_line.split(',')
    den_parts = den_line.split(',')

    #print den_parts[0] + ' , ' + num_parts[0]

    return 100 * float(num_parts[0]) / float(den_parts[0])


# Open the data files
f = open('perf.data', 'r')
cf = open('cache-miss-percentage.data', 'w')
bf = open('branch-miss-percentage.data', 'w')

# Iterator allows for the next() method
f_iter = iter(f)

for line in f_iter:
    # Record the x-axis values
    if ',' not in line and (line.startswith('1') or line.startswith('3')):
        cf.write('\n')
        bf.write('\n')

        cf.write(line.rstrip())
        bf.write(line.rstrip())

        cf.write(' ')
        bf.write(' ')

        cref = next(f_iter)
        cmiss = next(f_iter)
        cpercent = percentage(cmiss, cref)

        bref = next(f_iter)
        bmiss = next(f_iter)
        bpercent = percentage(bmiss, bref)

        cf.write(str(cpercent))
        bf.write(str(bpercent))

        cf.write(' ')
        bf.write(' ')

        continue


    # Otherwise, skip lines that aren't 'cache-references' lines
    if 'cache-references' not in line:
        continue;

    # Grab the cache-misses line and calculcate percentage
    cmiss = next(f_iter)
    #print line + 'hahaaaa'
    #print cmiss
    cpercent = percentage(cmiss, line)

    # Then grab the branch lines and percentage
    bref = next(f_iter)
    bmiss = next(f_iter)
    #print bref + 'loooool'
    #print bmiss
    bpercent = percentage(bmiss, bref)

    cf.write(str(cpercent))
    bf.write(str(bpercent))

    cf.write(' ')
    bf.write(' ')
