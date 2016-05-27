
require 'rake'


class CProject

	include Rake::DSL

	class <<self
		attr_accessor :objDir
	end

	# def self.objDir=(a)
	# 	@objDir = a
	# end
	#
	# def self.objDir
	# 	@objDir
	# end

	attr_accessor :name, :dir, :binary, :srcs, :libs

	def initialize( n, args = {} )
		@name = n
		@dir = args[:dir] || name
		@binary = name + ".out"
		@srcs = args[:srcs] || []
		@libs = args[:libs] || []

		yield self if block_given?

		@dir = Pathname.new(@dir)
		@binary = @dir.join(@binary).to_s
		@srcs.map! { |src|
			@dir.join(src) unless File.exist?( src )
		}

		@libs = [@libs].flatten

		define_tasks
	end

	def object( file )
		p = Pathname.new(file)
		(CProject.objDir.join p.sub_ext('.o')).to_s
	end

	def objects
 		srcs.map {|f| object(f) }
	end

	def define_tasks

		task :all => "#{name}:compile"

		objectDirs = objects.map { |o| Pathname.new(o).dirname }

		objectDirs.each { |od|
			directory od do; mkdir od unless od.directory?; end
		}

		srcs.map { |o| o.dirname.to_s }.uniq.each { |dir|
			rule '.o' => ->(t){t.pathmap("#{dir}/%f").ext(".c")} do |t|
				sh *([CC.to_s] + CFlags + LDFlags + %W( -c  -o #{t.name} #{t.source} ))
			end
		}


		namespace name.to_sym do
			task :compile => objectDirs + [binary]

			file binary => objects+libs do |t|
					sh *([LD.to_s] + LDFlags + CFlags + %W( -o #{t.name} ) + t.sources )
			end

			task :debug => binary do |t|
				sh *[GDB.to_s, '-command=gdb.cmds', t.source]
			end
		end



		task :clean do
			sh *(['rm','-rf', binary] + objects)
		end
	end

end
