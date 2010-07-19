
import platform

common_opt_flags = ["-O3", "-Wall", "-DNDEBUG", "-mmmx", "-msse", "-msse2",
    "-msse3", "-mfpmath=sse", "-pipe", "-fomit-frame-pointer", "-ffast-math"]

opt_amd_flags = common_opt_flags + ["-m3dnow", "-march=k8"]
opt_eee_flags = common_opt_flags + ["-march=prescott"]

opt_amd = Environment(CXXFLAGS = ' '.join(opt_amd_flags))
opt_eee = Environment(CXXFLAGS = ' '.join(opt_eee_flags))

opt_gprof_amd = Environment(CXXFLAGS = "-O2 -pg")

simple_opt = Environment(CXXFLAGS = '-Wall -O2 -DNDEBUG -D__GOCUP_DEBUG -ffast-math -pipe -fomit-frame-pointer')

dbg = Environment(CXXFLAGS = '-Wall -g -D__GOCUP_DEBUG')

#env = opt_amd
#env = opt_gprof_amd
#env = dbg

env = simple_opt

objects_sources = [\
    'lineiterator.cc',
    'solution.cc',
    'dataloader.cc',
    'distancematrix.cc',
    'pmedproblem.cc',
    'options.cc',
    'pmedsolver.cc',
    'hillclimber.cc',
    'glhillclimber.cc',
    'sampleinitializer.cc',
    'vshop.cc',
    'utils.cc',
    'bloomclimber.cc',
]

objects = [env.Object(objsrc) for objsrc in objects_sources]

env.Program(['pmedian.cc'] + objects)
