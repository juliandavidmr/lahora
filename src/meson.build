lahora_sources = [
  'main.vala',
  'Application.vala',
]

lahora_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

#lahora_sources += gnome.compile_resources('lahora-resources',
#'lahora.gresource.xml',
#  c_name: 'lahora'
#)

executable('lahora', lahora_sources,
  vala_args: '--target-glib=2.50',
  dependencies: lahora_deps,
  install: true,
)
