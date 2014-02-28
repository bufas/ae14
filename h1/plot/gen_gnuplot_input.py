
# Define the classes of implementations
impl = {
    'implicit':     ['inorder', 'bfs', 'dfs'],
    'explicit_ptr': ['bfs_explicit', 'dfs_explicit'],
    'explicit_int': ['bfs_explicit_int', 'dfs_explicit_int', 'veb_explicit_int'],
    'explicit':     ['bfs_explicit', 'dfs_explicit', 'bfs_explicit_int', 'dfs_explicit_int', 'veb_explicit_int'],
    'all':          ['inorder', 'bfs', 'dfs', 'bfs_explicit', 'dfs_explicit', 'bfs_explicit_int', 'dfs_explicit_int', 'veb_explicit_int']
}

titles = {
    'inorder':          'Inorder',
    'bfs':              'BFS',
    'dfs':              'DFS',
    'bfs_explicit':     'BFS Explicit ptr',
    'dfs_explicit':     'DFS EXplicit ptr',
    'bfs_explicit_int': 'BFS Explicit int',
    'dfs_explicit_int': 'DFS Explicit int',
    'veb_explicit_int': 'vEB Explicit int'
}

perf_labels = {
    'BPU'      : ['Time in us', 'Branch mispredictions', 'BPU queries', 'Branch hit %'],
    'LL_CACHE' : ['Time in us', 'Last-level cache misses', 'Last-level cache accesses', 'Last-level cache hit %'],
    'L1_CACHE' : ['Time in us', 'Level 1 cache misses', 'Level 1 cache accesses', 'Level 1 cache hit %'],
    'DATA_TLB' : ['Time in us', 'TLB misses', 'TLB accesses', 'TLB hit %'],
}

blocks = {
    'time'  :  3,
    'miss'  :  6,
    'access':  9,
    'ratio' : 12
}

# Define helper functions
def make_header(output, xlabel, ylabel):
    print 'set output "res/plots/%s"' % output
    print 'set xlabel "%s"' % xlabel
    print 'set ylabel "%s"' % ylabel

# The paraneters are:
#     output: the name of the output file
#     impl:   the implementation to use (bfs, dfs, inorder, ...)
#     perf:   the performance measure (BPU, LL_CACHE, L1_CACHE, DATA_TLB)
#     block:  3 for time, 6 for perf miss, 9 for perf access, 12 for ratio
#     start:  the dataline from which to start
#     end:    plot only datalines up to this line
def make_plot(output, impl, perf, block, start=1, end=0):
    # Print the header
    make_header(output, 'log_2(#nodes)', perf_labels[perf][block/3 - 1])

    # Calc every string
    every = ''
    if start != 1 or end != 0:
        if end == 0: every = 'every ::%d' % (start)
        else:        every = 'every ::%d::%d' % (start, end)
    
    # Output the plot lines
    print 'plot \\'
    for i in impl:
        endl = '' if (i == impl[-1]) else ', \\'
        print '"res/%s.%s.bench.data" %s using (log($1)/log(2)):($%d/$2):($%d/$2):($%d/$2) title "%s" with errorlines%s' \
        % (i, perf, every, block, block+1, block+2, titles[i], endl)

    # Print som blank space so the file becomes readable
    print
    print

# Set the output to png
print 'set terminal png'
print

#===================================================#
# Plot small instances to test L1 cache misses
#===================================================#

# Test cache performance around cache sizes
make_plot('small_l1cache_time.png',  impl['all'], 'L1_CACHE', blocks['time'],  8, 14)
make_plot('medium_llcache_time.png', impl['all'], 'LL_CACHE', blocks['time'], 14, 19)
make_plot('large_nocache_time.png',  impl['all'], 'LL_CACHE', blocks['time'], 18)

make_plot('small_l1cache.png',       impl['all'], 'L1_CACHE', blocks['miss'],  8, 14)
make_plot('medium_llcache.png',      impl['all'], 'LL_CACHE', blocks['miss'], 14, 19)

# Plot all for every performance criteria
make_plot('all/time.png',          impl['all'], 'LL_CACHE', blocks['time'])

make_plot('all/perf_bpu.png',      impl['all'], 'BPU',      blocks['miss'])
make_plot('all/perf_l1cache.png',  impl['all'], 'L1_CACHE', blocks['miss'])
make_plot('all/perf_llcache.png',  impl['all'], 'LL_CACHE', blocks['miss'])
make_plot('all/perf_tlb.png',      impl['all'], 'LL_CACHE', blocks['miss'])

make_plot('all/ratio_bpu.png',     impl['all'], 'BPU',      blocks['ratio'])
make_plot('all/ratio_l1cache.png', impl['all'], 'L1_CACHE', blocks['ratio'])
make_plot('all/ratio_llcache.png', impl['all'], 'LL_CACHE', blocks['ratio'])
make_plot('all/ratio_tlb.png',     impl['all'], 'LL_CACHE', blocks['ratio'])
