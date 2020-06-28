.. _reconstruction_system_refine_registration:

Refine registration
-------------------------------------

Input arguments
``````````````````````````````````````

This script runs with ``python run_system.py [config] --refine``. In ``[config]``, ``["path_dataset"]`` should have subfolders ``fragments`` which stores fragments in ``.ply`` files and a pose graph in a ``.json`` file.

The main function runs ``local_refinement`` and ``optimize_posegraph_for_scene``. The first function performs pairwise registration on the pairs detected by :ref:`reconstruction_system_register_fragments`. The second function performs multiway registration.


Fine-grained registration
``````````````````````````````````````

.. literalinclude:: ../../../examples/Python/ReconstructionSystem/refine_registration.py
   :language: python
   :lineno-start: 38
   :lines: 5,39-90
   :linenos:

Two options are given for the fine-grained registration. The ``color`` option is recommended since it uses color information to prevent drift. See [Park2017]_ for details.


Multiway registration
``````````````````````````````````````

.. literalinclude:: ../../../examples/Python/ReconstructionSystem/refine_registration.py
   :language: python
   :lineno-start: 16
   :lines: 5,17-36
   :linenos:

This script uses the technique demonstrated in :ref:`multiway_registration`. Function ``update_posegrph_for_refined_scene`` builds a pose graph for multiway registration of all fragments. Each graph node represents a fragment and its pose which transforms the geometry to the global space.

Once a pose graph is built, function ``optimize_posegraph_for_scene`` is called for multiway registration.

.. literalinclude:: ../../../examples/Python/ReconstructionSystem/optimize_posegraph.py
   :language: python
   :lineno-start: 52
   :lines: 5,53-60
   :linenos:

Main registration loop
``````````````````````````````````````

The function ``make_posegraph_for_refined_scene`` below calls all the functions introduced above.

.. literalinclude:: ../../../examples/Python/ReconstructionSystem/refine_registration.py
   :language: python
   :lineno-start: 129
   :lines: 5,130-176
   :linenos:

The main workflow is: pairwise local refinement -> multiway registration.

Results
``````````````````````````````````````

The following is messages from pose graph optimization.

.. code-block:: sh

    [GlobalOptimizationLM] Optimizing PoseGraph having 14 nodes and 35 edges.
    Line process weight : 789.730200
    [Initial     ] residual : 1.208286e+04, lambda : 1.706306e+01
    [Iteration 00] residual : 2.410383e+03, valid edges : 22, time : 0.000 sec.
    [Iteration 01] residual : 8.127856e+01, valid edges : 22, time : 0.000 sec.
    [Iteration 02] residual : 8.031355e+01, valid edges : 22, time : 0.000 sec.
    Delta.norm() < 1.000000e-06 * (x.norm() + 1.000000e-06)
    [GlobalOptimizationLM] total time : 0.001 sec.
    [GlobalOptimizationLM] Optimizing PoseGraph having 14 nodes and 35 edges.
    Line process weight : 789.730200
    [Initial     ] residual : 8.031355e+01, lambda : 1.716826e+01
    Delta.norm() < 1.000000e-06 * (x.norm() + 1.000000e-06)
    [GlobalOptimizationLM] total time : 0.000 sec.
    CompensateReferencePoseGraphNode : reference : 0


There are 14 fragments and 52 valid matching pairs between fragments. After 23 iteration, 11 edges are detected to be false positive. After they are pruned, pose graph optimization runs again to achieve tight alignment.
