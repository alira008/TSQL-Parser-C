const std = @import("std");

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});

    const exe = b.addExecutable(.{ .name = "tsql-parser", .root_source_file = .{ .path = "src/main.c" }, .link_libc = true, .target = target, .optimize = optimize });

    exe.addCSourceFiles(&.{ "src/lexer.c", "src/arena.c" }, &.{
        "-std=c17",
        "-pedantic",
        "-Wall",
        "-Wextra",
        "-W",
        "-Wno-missing-field-initializers",
        "-fno-sanitize=undefined",
    });
    exe.addIncludePath(.{ .path = "src" });

    b.installArtifact(exe);
    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the program");
    run_step.dependOn(&run_cmd.step);
}
