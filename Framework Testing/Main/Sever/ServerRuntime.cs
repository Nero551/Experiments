using System;
using System.Collections.Generic;
using Godot;
using Processors;

sealed class ServerRuntime : Runtime
{
    public override void Start()
    {
        Server.Start();

        base.Start();
    }

    public override void Process(double delta)
    {
        Server.Process(delta);

        base.Process(delta);
    }

    public override void PhysicsProcess(double delta)
    {
        base.PhysicsProcess(delta);
    }
}
