/**
@page step_49 The step-49 tutorial program
This tutorial depends on step-1.

@htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Generalconcernsaboutmeshes">General concerns about meshes</a>
        <li><a href="#Howtocreatemeshes">How to create meshes</a>
      <ul>
        <li><a href="#UsingGridGenerator">Using GridGenerator</a>
        <li><a href="#Constructingyourownmeshprogrammatically">Constructing your own mesh programmatically</a>
        <li><a href="#Importingfromexternalprograms">Importing from external programs</a>
      </ul>
        <li><a href="#ModifyingaMesh">Modifying a Mesh</a>
      <ul>
        <li><a href="#Transformations">Transformations</a>
        <li><a href="#MergingMeshes">Merging Meshes</a>
        <li><a href="#MovingVertices">Moving Vertices</a>
        <li><a href="#ExtrudingMeshes">Extruding Meshes</a>
      </ul>
        <li><a href="#Afteryouhaveacoarsemesh"> After you have a coarse mesh </a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Includefiles">Include files</a>
        <li><a href="#Generatingoutputforagivenmesh">Generating output for a given mesh</a>
        <li><a href="#Mainroutines">Main routines</a>
      <ul>
        <li><a href="#grid_1Loadingameshgeneratedbygmsh">grid_1: Loading a mesh generated by gmsh</a>
        <li><a href="#grid_2Mergingtriangulations">grid_2: Merging triangulations</a>
        <li><a href="#grid_3Movingvertices">grid_3: Moving vertices</a>
        <li><a href="#grid_4Demonstratingextrude_triangulation">grid_4: Demonstrating extrude_triangulation</a>
        <li><a href="#grid_5DemonstratingGridToolstransformpart1">grid_5: Demonstrating GridTools::transform, part 1</a>
        <li><a href="#grid_6DemonstratingGridToolstransformpart2">grid_6: Demonstrating GridTools::transform, part 2</a>
        <li><a href="#grid_7Demonstratingdistort_random">grid_7: Demonstrating distort_random</a>
      </ul>
        <li><a href="#Themainfunction">The main function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a>
    <ul>
        <li><a href="#NextstepsCurvedCells">Next steps: Curved Cells</a>
        <li><a href="#Possibilitiesforextensions"> Possibilities for extensions </a>
      <ul>
        <li><a href="#Assigningdifferentboundaryids"> Assigning different boundary ids </a>
        <li><a href="#Extractingaboundarymesh"> Extracting a boundary mesh </a>
    </ul>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
examples/step-49/doc/intro.dox

<i>This program was contributed by Timo Heister. Parts of the results section
were contributed by Yuhan Zhou, Wolfgang Bangerth, and David Wells.</i>

<a name="Intro"></a>

<a name="Introduction"></a><h1> Introduction </h1> 本教程是步骤1的扩展，演示了几种获得比那里显示的更多的网格的方法。


 @note  本教程也可作为Jupyter Python笔记本，使用deal.II python接口。该笔记本与原始的C++程序在同一目录下提供。

生成复杂的几何图形是一项具有挑战性的任务，特别是在三个空间维度。我们将讨论几种方法，但这个清单并不详尽。此外，没有一种方法适合所有的问题。

这个例子程序显示了一些为计算而创建和修改网格的方法，并以与我们在步骤1中相同的方式将它们输出为 <code>.vtu</code> 文件。没有做其他的计算或自适应细化；我们的想法是，你可以在其他更多的模拟器中使用这里的技术作为构建模块。请注意，这个例子程序并没有展示本介绍中讨论的所有生成网格的方法。




<a name="Generalconcernsaboutmeshes"></a><h3>General concerns about meshes</h3>


当你使用自适应网格细化时，你肯定希望初始网格尽可能地粗大。因为只要你有内存和CPU时间，你就可以用自适应细化技术把它做得越细越好。然而，这就要求你不要把网格单元浪费在域的某些地方，因为这些单元是没有价值的。因此，你不希望从一个太细的网格开始，因为这已经占用了你的单元预算的很大一部分，而且你无法粗化初始网格中的单元。

也就是说，你的网格需要充分捕捉给定的几何体。




<a name="Howtocreatemeshes"></a><h3>How to create meshes</h3>


有几种方法来创建一个初始网格。网格可以通过多种方式进行修改或组合，这一点将在后面讨论。

<a name="UsingGridGenerator"></a><h4>Using GridGenerator</h4>


生成网格的最简单方法是使用命名空间GridGenerator中的函数，这在步骤1中已经讨论过了。  有许多不同的辅助函数可用，包括 GridGenerator::hyper_cube(),   GridGenerator::hyper_shell(),   GridGenerator::hyper_ball(),  和  GridGenerator::hyper_cube_with_cylindrical_hole().  。




<a name="Constructingyourownmeshprogrammatically"></a><h4>Constructing your own mesh programmatically</h4>


如果GridGenerator命名空间中没有适合你想做的事情，你总是可以在你的程序中 "手工 "创建一个三角图。为此，你需要一个带有坐标的顶点列表和一个引用这些顶点的单元格列表。你可以在步骤14的函数<tt>create_coarse_grid()</tt>中找到一个例子。GridGenerator中的所有函数都以这种方式实现。

我们很乐意接受更多的功能加入到GridGenerator中。因此，如果你最终写了一个可能对更多人有用的函数，请将其贡献出来。




<a name="Importingfromexternalprograms"></a><h4>Importing from external programs</h4>


GridIn类可以从磁盘的文件中读取许多不同的网格格式。如何做到这一点，在步骤5中有解释，在本例中可以看到函数 <code>grid_1</code> ，见下面的代码。

网格可以由不同的工具生成，如<a
href="http://gmsh.info" target="_top">gmsh</a>、<a
href="https://lagrit.lanl.gov/" target="_top">lagrit</a>和<a
href="http://cubit.sandia.gov/" target="_top">cubit</a>。更多信息见GridIn的文档。问题是，deal.II需要的网格只由四边形和六面体组成--四面体的网格无法工作（这意味着不能直接使用tetgen等工具）。

我们将描述一个使用%Gmsh的可能工作流程。%Gmsh是我们所知道的最小和最快速设置的开源工具。它可以生成非结构化的二维四面体网格。在三维中，它可以挤压二维网格以获得六面体网格；将非结构化几何体三维网格化为六面体是可能的，尽管这些网格的质量有一些问题，意味着这些网格有时只能在交易中工作。

在%Gmsh中，一个网格的基本描述是基于文本的 <code>.geo</code> 文件，其格式可以包含计算、循环、变量等。这种格式在允许描述复杂的几何图形方面是相当灵活的。然后，网格是由表面表示法生成的，表面表示法是由线条循环列表建立的，线条循环列表又是由点建立的。 <code>.geo</code>  脚本可以用手写和编辑，也可以通过在%Gmsh内用图形创建对象来自动生成。在许多情况下，最好是把这两种方法结合起来。如果你想用手写的话，可以在 "几何 "选项卡下按 "重载 "来轻松地重新加载文件，并在gmsh的图形用户界面上看到效果。

本教程包含一个例子 <code>.geo</code> 文件，描述一个内部有两个物体被切割出来的盒子。这就是 <code>example.geo</code> 在%Gmsh中的样子（显示边界指标以及下面要讨论的网格）。

 <img src="https://www.dealii.org/images/steps/developer/step-49.gmsh_picture.png" alt=""> 

你可能想用文本编辑器打开 <code>example.geo</code> 文件（它与<tt>step-49.cc</tt>源文件位于同一目录），看看它是如何结构的。你可以看到域的边界是如何由一些线组成的，后来我们把几条线组合成 "物理线"（或 "物理面"），列出逻辑线的编号。"物理 "对象是携带边界指标信息的对象（见 @ref GlossBoundaryIndicator "本词汇表条目"）。

 @note  这个文件包含 "物理线 "和 "物理面 "是很重要的。它们提供了在deal.II中使用的边界指标和材料ID。没有这些物理实体，任何东西都不会被导入deal.II中。

deal.II的GridIn类可以读取%Gmsh编写的 <code>.msh</code> 格式，该格式包含为 <code>.geo</code> file. You generate the <code>.msh</code> 描述的几何体创建的网格，通过运行指令

@code
gmsh -2 example.geo
@endcode



在命令行中，或者在加载文件后点击%Gmsh中的 "Mesh "和 "2D"。  现在这是从 <code>.msh</code> 文件中读取的网格，并由deal.II再次保存为图像（见当前程序的 <code>grid_1</code> 功能）。

 <img src="https://www.dealii.org/images/steps/developer/step-49.grid-1.png" alt=""> 

 @note  %Gmsh有许多其他接口，人们可以通过这些接口来描述几何图形。特别是，它能够与Python和Julia等脚本语言连接，但也可以用C++编写脚本。这些接口很有用，如果人们不只是想为一个单一的几何体生成网格（在这种情况下，图形界面或者在简单的情况下，手写的".geo "文件可能是最简单的方法），而是想对几何体进行参数化研究，为此需要为某些参数不同的几何体生成许多网格。另一种情况是，如果已经有一个CAD几何体，只需要一个网格；事实上，这可以在deal.II中使用 Gmsh::create_triangulation_from_boundary_curve() 函数来完成。




<a name="ModifyingaMesh"></a><h3>Modifying a Mesh</h3>


在以上述方式获得一个（或几个）网格后，在将其用于有限元计算之前，有许多方法可以对其进行操作。




<a name="Transformations"></a><h4>Transformations</h4>


GridTools命名空间包含了一系列的小函数，用于以各种方式转换给定的网格。函数  GridTools::shift,   GridTools::rotate,   GridTools::scale  的用法相当明显，所以我们在此不讨论这些函数。

函数 GridTools::transform 允许你使用平滑函数对给定网格的顶点进行变换。在step-38的结果部分也给出了它的使用实例，但让我们在这里展示一个更简单的例子。在当前程序的函数 <code>grid_5()</code> 中，我们用正弦曲线对网格的y坐标进行扰动。

 <table width="60%" align="center">
  <tr>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-5a.png" alt=""> regular input mesh
    </td>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-5.png" alt=""> output mesh
    </td>
  </tr>
</table> 

同样地，我们可以用公式  $(x,y) \mapsto (x,\tanh(2 y)/\tanh(2))$  将一个有规律的细化单位方格转换为y方向的墙体适应网格。这在本教程的  <code>grid_6()</code>  中完成。   <table width="60%" align="center">
  <tr>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-6a.png" alt=""> regular input mesh
    </td>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-6.png" alt=""> wall-adapted output mesh
    </td>
  </tr>
</table> 

最后，函数 GridTools::distort_random 允许你将网格中的顶点（可选择忽略边界节点）随机移动。这在 <code>grid_7()</code> 中进行了演示，其结果如下。

 <table width="60%" align="center">
  <tr>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-7a.png" alt=""> regular input mesh
    </td>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-7.png" alt=""> perturbed output mesh
    </td>
  </tr>
</table> 

这个函数主要是为了否定在研究常规网格收敛时得到的一些超收敛效应，以及抑制deal.II中的一些优化，这些优化可以利用单元格形状相似的事实。超级收敛是指如果一个网格具有某些对称性--例如，如果进入一个顶点的边对这个顶点是对称的，并且如果对一个单元的所有顶点都是这样的话

归根结底，这是由于如果对误差进行泰勒扩展，对称性导致了这样一个事实，即预期的扩展的下一个项恰好是零，而误差的阶数是由*第二个下*项决定的。一个扭曲的网格没有这些对称性，因此误差反映了在*任何*种网格上解方程时将会看到的情况，而不是显示只反映特定情况的东西)。




<a name="MergingMeshes"></a><h4>Merging Meshes</h4>


该函数 GridGenerator::merge_triangulations() 允许你将两个给定的三角形对象合并为一个。  要做到这一点，共享边或面的顶点必须完全匹配。  排列两个网格可以用  GridTools::shift  和  GridTools::scale.  来实现。 在本教程的函数  <code>grid_2()</code>  中，我们合并了一个带圆孔的正方形（用  GridGenerator::hyper_cube_with_cylindrical_hole())  生成）和一个矩形（用  GridGenerator::subdivided_hyper_rectangle()).  生成）。 函数  GridGenerator::subdivided_hyper_rectangle()  允许你指定重复的数量和角的位置，所以这里不需要手动移动三角网格。你应该以图形方式检查网格，以确保单元格排布正确，并且在合并后的三角图中不存在未配对的节点。

这些是输入网格和输出网格。

 <table width="80%" align="center">
  <tr>
    <td align="center"><img src="https://www.dealii.org/images/steps/developer/step-49.grid-2a.png" alt="" height="200px">input mesh 1</td>
    <td align="center"><img src="https://www.dealii.org/images/steps/developer/step-49.grid-2b.png" alt="" height="200px">input mesh 2</td>
    <td align="center"><img src="https://www.dealii.org/images/steps/developer/step-49.grid-2.png" alt="" height="200px">merged mesh</td>
  </tr>
</table> 




<a name="MovingVertices"></a><h4>Moving Vertices</h4>


函数  <code>grid_3()</code>  展示了在现有网格中挑选个别顶点并移动它们的能力。请注意，这有可能产生退化的或倒置的单元，你不应该期望使用这样的网格会产生任何有用的东西。在这里，我们通过向上移动顶部顶点来创建一个不完全居中的圆柱形孔的盒子。

 <table width="60%" align="center">
  <tr>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-3a.png" alt="" height="200px"> input mesh
    </td>
    <td align="center">
        <img src="https://www.dealii.org/images/steps/developer/step-49.grid-3.png" alt="" height="200px"> top vertices moved upwards
    </td>
  </tr>
</table> 

关于如何做到这一点的确切方法，见下面的代码。




<a name="ExtrudingMeshes"></a><h4>Extruding Meshes</h4>


如果你需要一个可以通过挤压给定的2D网格（可以通过上述任何一种方式创建）来创建的3D网格，你可以使用函数  GridGenerator::extrude_triangulation().  参见本教程中的  <code>grid_4()</code>  函数为例。请注意，对于这个特殊的情况，所给的结果也可以用3D版本的 GridGenerator::hyper_cube_with_cylindrical_hole(). 来实现。主要的用法是一个2D网格，例如用%Gmsh生成，如上所述从 <code>.msh</code> 文件中读入。这是grid_4()的输出。

 <table width="60%" align="center">
  <tr>
    <td align="center">
      <img src="https://www.dealii.org/images/steps/developer/step-49.grid-4base.png" alt=""> input mesh
    </td>
    <td align="center">
      <img src="https://www.dealii.org/images/steps/developer/step-49.grid-4.png" alt=""> extruded output mesh
    </td>
  </tr>
</table> 




<a name="Afteryouhaveacoarsemesh"></a><h3> After you have a coarse mesh </h3>


使用上面讨论的方法创建一个粗略的网格只是第一步。当你有了它，它通常可以作为进一步细化网格的基础。这并不困难，事实上，如果你的几何体只由直面组成，那就没有其他事情可做。然而，如果你有一个更复杂的几何体，情况往往就不是这样了，除了创建网格之外，还有更多的步骤是必须的。我们将在下面的<a href="#Results">results section</a>中详细介绍这些步骤。


 *
 *
 * <a name="CommProg"></a>
 * <h1> The commented program</h1>
 * 
 * 这个教程程序很奇怪，与其他大多数步骤不同，介绍中已经提供了关于如何使用各种策略来生成网格的大部分信息。因此，这里没有什么需要评论的，我们在代码中穿插了相对较少的文字。从本质上讲，这里的代码只是提供了一个在介绍中已经描述过的内容的参考实现。
 * 

 * 
 * 
 * <a name="Includefiles"></a> 
 * <h3>Include files</h3>
 * 
 * @code
 * #include <deal.II/grid/tria.h> 
 * #include <deal.II/grid/grid_generator.h> 
 * #include <deal.II/grid/grid_tools.h> 
 * #include <deal.II/grid/manifold_lib.h> 
 * #include <deal.II/grid/grid_out.h> 
 * #include <deal.II/grid/grid_in.h> 
 * 
 * #include <iostream> 
 * #include <fstream> 
 * 
 * #include <map> 
 * 
 * using namespace dealii; 
 * @endcode
 * 
 * 
 * <a name="Generatingoutputforagivenmesh"></a> 
 * <h3>Generating output for a given mesh</h3>
 * 

 * 
 * 下面的函数为我们将在本程序的剩余部分中生成的任何网格生成一些输出。特别是，它生成了以下信息。
 * 

 * 
 * 

 * 
 * 

 * 
 * - 一些关于这个网格所处的空间维数和它的单元数的一般信息。
 * 

 * 
 * - 使用每个边界指标的边界面的数量，这样就可以和我们预期的情况进行比较。
 * 

 * 
 * 最后，该函数将网格输出为VTU格式，可以方便地在Paraview或VisIt中进行可视化。
 * 

 * 
 * 
 * @code
 * template <int dim> 
 * void print_mesh_info(const Triangulation<dim> &triangulation, 
 *                      const std::string &       filename) 
 * { 
 *   std::cout << "Mesh info:" << std::endl 
 *             << " dimension: " << dim << std::endl 
 *             << " no. of cells: " << triangulation.n_active_cells() << std::endl; 
 * 
 * @endcode
 * 
 * 接下来循环所有单元格的所有面，找出每个边界指标的使用频率（请记住，如果你访问一个不存在的 std::map 对象的元素，它将被隐式创建并默认初始化--在当前情况下为零--然后我们再将其增加）。
 * 

 * 
 * 
 * @code
 *   { 
 *     std::map<types::boundary_id, unsigned int> boundary_count; 
 *     for (const auto &face : triangulation.active_face_iterators()) 
 *       if (face->at_boundary()) 
 *         boundary_count[face->boundary_id()]++; 
 * 
 *     std::cout << " boundary indicators: "; 
 *     for (const std::pair<const types::boundary_id, unsigned int> &pair : 
 *          boundary_count) 
 *       { 
 *         std::cout << pair.first << "(" << pair.second << " times) "; 
 *       } 
 *     std::cout << std::endl; 
 *   } 
 * 
 * @endcode
 * 
 * 最后，产生一个网格的图形表示到一个输出文件。
 * 

 * 
 * 
 * @code
 *   std::ofstream out(filename); 
 *   GridOut       grid_out; 
 *   grid_out.write_vtu(triangulation, out); 
 *   std::cout << " written to " << filename << std::endl << std::endl; 
 * } 
 * @endcode
 * 
 * 
 * <a name="Mainroutines"></a> 
 * <h3>Main routines</h3>
 * 
 * <a name="grid_1Loadingameshgeneratedbygmsh"></a> 
 * <h4>grid_1: Loading a mesh generated by gmsh</h4>
 * 

 * 
 * 在这第一个例子中，我们展示了如何加载我们在介绍中讨论过的如何生成的网格。这与 step-5 中加载网格的模式相同，尽管那里是以不同的文件格式（UCD而不是MSH）编写。
 * 

 * 
 * 
 * @code
 * void grid_1() 
 * { 
 *   Triangulation<2> triangulation; 
 * 
 *   GridIn<2> gridin; 
 *   gridin.attach_triangulation(triangulation); 
 *   std::ifstream f("example.msh"); 
 *   gridin.read_msh(f); 
 * 
 *   print_mesh_info(triangulation, "grid-1.vtu"); 
 * } 
 * @endcode
 * 
 * 
 * <a name="grid_2Mergingtriangulations"></a> 
 * <h4>grid_2: Merging triangulations</h4>
 * 

 * 
 * 在这里，我们首先创建两个三角形，然后将它们合并成一个。 正如介绍中所讨论的，必须确保共同界面的顶点位于相同的坐标上。
 * 

 * 
 * 
 * @code
 * void grid_2() 
 * { 
 *   Triangulation<2> tria1; 
 *   GridGenerator::hyper_cube_with_cylindrical_hole(tria1, 0.25, 1.0); 
 * 
 *   Triangulation<2>          tria2; 
 *   std::vector<unsigned int> repetitions(2); 
 *   repetitions[0] = 3; 
 *   repetitions[1] = 2; 
 *   GridGenerator::subdivided_hyper_rectangle(tria2, 
 *                                             repetitions, 
 *                                             Point<2>(1.0, -1.0), 
 *                                             Point<2>(4.0, 1.0)); 
 * 
 *   Triangulation<2> triangulation; 
 *   GridGenerator::merge_triangulations(tria1, tria2, triangulation); 
 * 
 *   print_mesh_info(triangulation, "grid-2.vtu"); 
 * } 
 * @endcode
 * 
 * 
 * <a name="grid_3Movingvertices"></a> 
 * <h4>grid_3: Moving vertices</h4>
 * 

 * 
 * 在这个函数中，我们移动一个网格的顶点。这比人们通常想象的要简单：如果你用 <code>cell-@>vertex(i)</code> 询问一个单元格的 <code>i</code> 的顶点的坐标，它不只是提供这个顶点的位置，实际上是对存储这些坐标的位置的引用。然后我们可以修改存储在那里的值。
 * 

 * 
 * 所以这就是我们在这个函数的第一部分所做的。我们创建一个几何形状为 $[-1,1]^2$ 的正方形，在原点处有一个半径为0.25的圆孔。然后我们在所有单元格和所有顶点上循环，如果一个顶点的 $y$ 坐标等于1，我们就把它向上移动0.5。
 * 

 * 
 * 注意，这种程序通常不是这样工作的，因为通常会多次遇到相同的顶点，并且可能会多次移动它们。它在这里起作用是因为我们根据顶点的几何位置来选择要使用的顶点，而移动过一次的顶点在未来将无法通过这个测试。解决这个问题的一个更普遍的方法是保留一个 std::set ，即那些我们已经移动过的顶点索引（我们可以用 <code>cell-@>vertex_index(i)</code> 获得，并且只移动那些索引还不在这个集合中的顶点。
 * 

 * 
 * 
 * @code
 * void grid_3() 
 * { 
 *   Triangulation<2> triangulation; 
 *   GridGenerator::hyper_cube_with_cylindrical_hole(triangulation, 0.25, 1.0); 
 * 
 *   for (const auto &cell : triangulation.active_cell_iterators()) 
 *     { 
 *       for (const auto i : cell->vertex_indices()) 
 *         { 
 *           Point<2> &v = cell->vertex(i); 
 *           if (std::abs(v(1) - 1.0) < 1e-5) 
 *             v(1) += 0.5; 
 *         } 
 *     } 
 * 
 * @endcode
 * 
 * 在第二步，我们将对网格进行两次细化。为了正确做到这一点，我们应该沿着以原点为中心的圆的表面在内部边界上放置新的点。幸运的是， GridGenerator::hyper_cube_with_cylindrical_hole 已经在内部边界上附加了一个Manifold对象，所以我们不需要做任何事情，只需要细化网格（参见<a href="#Results">results section</a>中一个完全可行的例子，我们 <em> 做 </em> 附加一个Manifold对象）。
 * 

 * 
 * 
 * @code
 *   triangulation.refine_global(2); 
 *   print_mesh_info(triangulation, "grid-3.vtu"); 
 * } 
 * 
 * @endcode
 * 
 * 如上图所示，做事有一个障碍。如果像这里所示的那样移动边界上的节点，由于内部的节点没有被移动，所以经常会出现内部的单元被严重扭曲的情况。在目前的情况下，这并不是一个很大的问题，因为当节点被移动时，网格并不包含任何内部节点--它是粗略的网格，而且恰好所有的顶点都在边界上。还有一种情况是，我们在这里的移动，与平均单元的大小相比，并没有太大影响。然而，有时我们确实想把顶点移动一段距离，在这种情况下，我们也需要移动内部节点。一个自动完成的方法是调用函数 GridTools::laplace_transform ，该函数接收一组转换后的顶点坐标并移动所有其他的顶点，使产生的网格在某种意义上有一个小的变形。
 * 

 * 
 * 
 * <a name="grid_4Demonstratingextrude_triangulation"></a> 
 * <h4>grid_4: Demonstrating extrude_triangulation</h4>
 * 

 * 
 * 这个例子从前面的函数中获取初始网格，并简单地将其挤压到第三空间维度。
 * 

 * 
 * 
 * @code
 * void grid_4() 
 * { 
 *   Triangulation<2> triangulation; 
 *   Triangulation<3> out; 
 *   GridGenerator::hyper_cube_with_cylindrical_hole(triangulation, 0.25, 1.0); 
 * 
 *   GridGenerator::extrude_triangulation(triangulation, 3, 2.0, out); 
 *   print_mesh_info(out, "grid-4.vtu"); 
 * } 
 * @endcode
 * 
 * 
 * <a name="grid_5DemonstratingGridToolstransformpart1"></a> 
 * <h4>grid_5: Demonstrating GridTools::transform, part 1</h4>
 * 

 * 
 * 这个例子和下一个例子首先创建一个网格，然后根据一个函数移动网格的每个节点，这个函数接收一个点并返回一个映射的点。在这个例子中，我们转换  $(x,y) \mapsto (x,y+\sin(\pi x/5))$  。
 * 

 * 
 * GridTools::transform()  需要一个三角形和一个参数，这个参数可以像一个函数一样被调用，接收一个点并返回一个点。有不同的方式来提供这样一个参数。它可以是一个函数的指针；它可以是一个具有`operator()`的类的对象；它可以是一个lambda函数；或者它可以是任何通过 <code>std::function@<Point@<2@>(const Point@<2@>)@></code> 对象描述的东西。
 * 

 * 
 * 更现代的方法是使用一个接受一个点并返回一个点的lambda函数，这就是我们在下面所做的。
 * 

 * 
 * 
 * @code
 * void grid_5() 
 * { 
 *   Triangulation<2>          triangulation; 
 *   std::vector<unsigned int> repetitions(2); 
 *   repetitions[0] = 14; 
 *   repetitions[1] = 2; 
 *   GridGenerator::subdivided_hyper_rectangle(triangulation, 
 *                                             repetitions, 
 *                                             Point<2>(0.0, 0.0), 
 *                                             Point<2>(10.0, 1.0)); 
 * 
 *   GridTools::transform( 
 *     [](const Point<2> &in) { 
 *       return Point<2>(in[0], in[1] + std::sin(numbers::PI * in[0] / 5.0)); 
 *     }, 
 *     triangulation); 
 *   print_mesh_info(triangulation, "grid-5.vtu"); 
 * } 
 * 
 * @endcode
 * 
 * 
 * <a name="grid_6DemonstratingGridToolstransformpart2"></a> 
 * <h4>grid_6: Demonstrating GridTools::transform, part 2</h4>
 * 

 * 
 * 在第二个例子中，我们将使用映射  $(x,y) \mapsto (x,\tanh(2y)/\tanh(2))$  将原始网格中的点转换为新的网格。为了使事情更有趣，而不是像前面的例子那样在一个单一的函数中完成，我们在这里创建一个具有  <code>operator()</code>  的对象，这个对象将被  GridTools::transform.  所调用。当然，这个对象实际上可能要复杂得多：这个对象可能有成员变量，在计算顶点的新位置时起作用。
 * 

 * 
 * 
 * @code
 * struct Grid6Func 
 * { 
 *   double trans(const double y) const 
 *   { 
 *     return std::tanh(2 * y) / tanh(2); 
 *   } 
 * 
 *   Point<2> operator()(const Point<2> &in) const 
 *   { 
 *     return {in(0), trans(in(1))}; 
 *   } 
 * }; 
 * 
 * void grid_6() 
 * { 
 *   Triangulation<2>          triangulation; 
 *   std::vector<unsigned int> repetitions(2); 
 *   repetitions[0] = repetitions[1] = 40; 
 *   GridGenerator::subdivided_hyper_rectangle(triangulation, 
 *                                             repetitions, 
 *                                             Point<2>(0.0, 0.0), 
 *                                             Point<2>(1.0, 1.0)); 
 * 
 *   GridTools::transform(Grid6Func(), triangulation); 
 *   print_mesh_info(triangulation, "grid-6.vtu"); 
 * } 
 * @endcode
 * 
 * 
 * <a name="grid_7Demonstratingdistort_random"></a> 
 * <h4>grid_7: Demonstrating distort_random</h4>
 * 

 * 
 * 在这最后一个例子中，我们创建了一个网格，然后通过随机扰动使其（内部）顶点变形。这不是你想在生产计算中做的事情（因为在具有 "良好形状 "单元的网格上的结果通常比在 GridTools::distort_random()), 产生的变形单元上的结果要好，但这是一个有用的工具，可以测试离散化和代码，确保它们不会因为网格恰好是均匀结构和支持超级收敛特性而意外地工作。
 * 

 * 
 * 
 * @code
 * void grid_7() 
 * { 
 *   Triangulation<2>          triangulation; 
 *   std::vector<unsigned int> repetitions(2); 
 *   repetitions[0] = repetitions[1] = 16; 
 *   GridGenerator::subdivided_hyper_rectangle(triangulation, 
 *                                             repetitions, 
 *                                             Point<2>(0.0, 0.0), 
 *                                             Point<2>(1.0, 1.0)); 
 * 
 *   GridTools::distort_random(0.3, triangulation, true); 
 *   print_mesh_info(triangulation, "grid-7.vtu"); 
 * } 
 * @endcode
 * 
 * 
 * <a name="Themainfunction"></a> 
 * <h3>The main function</h3>
 * 

 * 
 * 最后是主函数。这里没有什么可做的，只是调用我们上面写的所有各种函数。
 * 

 * 
 * 
 * @code
 * int main() 
 * { 
 *   try 
 *     { 
 *       grid_1(); 
 *       grid_2(); 
 *       grid_3(); 
 *       grid_4(); 
 *       grid_5(); 
 *       grid_6(); 
 *       grid_7(); 
 *     } 
 *   catch (std::exception &exc) 
 *     { 
 *       std::cerr << std::endl 
 *                 << std::endl 
 *                 << "----------------------------------------------------" 
 *                 << std::endl; 
 *       std::cerr << "Exception on processing: " << std::endl 
 *                 << exc.what() << std::endl 
 *                 << "Aborting!" << std::endl 
 *                 << "----------------------------------------------------" 
 *                 << std::endl; 
 * 
 *       return 1; 
 *     } 
 *   catch (...) 
 *     { 
 *       std::cerr << std::endl 
 *                 << std::endl 
 *                 << "----------------------------------------------------" 
 *                 << std::endl; 
 *       std::cerr << "Unknown exception!" << std::endl 
 *                 << "Aborting!" << std::endl 
 *                 << "----------------------------------------------------" 
 *                 << std::endl; 
 *       return 1; 
 *     } 
 * } 
 * 
 * 
 * @endcode
examples/step-49/doc/results.dox



<a name="Results"></a><h1>Results</h1>


该程序产生一系列 <code>.vtu</code> 的三角形文件。这些方法已在上文讨论。




<a name="NextstepsCurvedCells"></a><h3>Next steps: Curved Cells</h3>


正如介绍中提到的，使用这里讨论的方法创建一个粗略的网格只是第一步。为了细化网格，Triangulation需要知道在边、面和单元格的中点上放置新的顶点。默认情况下，这些新的点会被放置在周围点的算术平均值上，但如果你需要的是粗略网格没有充分解决的弯曲边界，这并不是你想要的。例如，对于这个网格，中心孔应该是圆形的。

 <img src="https://www.dealii.org/images/steps/developer/step-49.grid-2a.png" alt="" height="200px"> 

如果你只是简单地细化它，三角测量类就不能知道你是想让孔变成圆形还是八角形。默认的做法是沿着现有的直线放置新的点。经过两个网格细化步骤后，这将产生以下的网格，这不是我们想要的。

 <img src="https://www.dealii.org/images/steps/developer/step-49.grid-2d-refined.png" alt="" height="200px"> 

需要发生的是，你告诉三角函数，你实际上是想使用一个弯曲的几何体。做到这一点的方法需要三个步骤。

- 创建一个描述所需几何图形的对象。这个对象将在细化三角图以获得新的点位置时被查询。如果在系统组装过程中使用了MappingQ或MappingQGeneric这样的高阶映射，它也将被用来计算形状函数值。   在deal.II中，Manifold类和继承自它的类（如PolarManifold和FlatManifold）执行这些计算。

- 通知Triangulation对象使用哪个Manifold类。默认情况下，Triangulation使用FlatManifold来进行所有的几何计算，它假定所有的单元格边缘都是直线，所有的四边形都是平的。你可以通过调用 Triangulation::set_manifold 函数将Manifold类附加到Triangulation上，该函数将 <code>manifold_id</code> 与Manifold对象关联。关于这方面的更多信息，请参见 @ref GlossManifoldIndicator "关于这个主题的词汇表条目"。

- 最后，你必须用正确的 <code>manifold_id</code> 标记单元和单元面。例如，你可以通过以下方式得到一个在直角坐标中带有弯曲单元的环形扇面（但在极坐标中是矩形）。   @code
  Triangulation<2> tria;
  GridGenerator::hyper_cube(tria);
  const auto cell = tria.begin_active();
  cell->vertex(2) = Point<2>(-0.5, 1.0);
  cell->vertex(3) = Point<2>(1.5, 1.0);
  tria.set_all_manifold_ids(42);
  tria.set_manifold(42, PolarManifold<2>(Point<2>(0.5, -1.0)));
  tria.refine_global(3);
  @endcode

  现在，当网格被细化时，所有的单元格分割计算都将在极坐标中进行。

GridGenerator命名空间中的所有函数，如果创建的网格中的某些单元应该是弯曲的，也会将正确的Manifold对象附加到所提供的Triangulation上：也就是说，对于这些函数，我们默认会得到正确的行为。然而，对于手工生成的网格，情况要有趣得多。

为了更详细地说明这个过程，让我们考虑一个由Yuhan Zhou创建的例子，作为2013年德克萨斯A&amp;M大学的一个学期项目的一部分。目标是生成（和使用）一个描述微观结构的电气设备的几何体。在一个CAD程序中，这个几何体看起来像这样。

 <img src="https://www.dealii.org/images/steps/developer/step-49.yuhan.1.png" alt=""> 

在下文中，我们将引导你完成为这个几何体创建网格的整个过程，包括通过展示可能出错的一些常见陷阱。

实现这一目标的第一步是创建一个粗略的网格，通过为每个截面创建一个2D粗略的网格，将它们挤压到第三个方向，然后将它们粘在一起。下面的代码使用之前描述的技术来完成这个工作。

@code
// Given a list of points and how vertices connect to cells, create a
// mesh. This is in the same way as we do in step 14.
void create_2d_grid(
  const std::vector<Point<2>> &vertices,
  const std::vector<
    std::array<unsigned int, GeometryInfo<2>::vertices_per_cell>>
    &               vertex_indices,
  Triangulation<2> &coarse_grid)
{
  std::vector<CellData<2>> cells(vertex_indices.size());
  for (unsigned int i = 0; i < cells.size(); ++i)
    {
      for (unsigned int j = 0; j < vertex_indices[i].size(); ++j)
        cells[i].vertices[j] = vertex_indices[i][j];
    }


  coarse_grid.create_triangulation(vertices, cells, SubCellData());
}



// Create a triangulation that covers the entire volume
void create_3d_grid(Triangulation<3> &triangulation)
{
  // Generate first cross section
  const std::vector<Point<2>> vertices_1{{-1.5, 0.},
                                         {-0.5, 0.},
                                         {0.5, 0.},
                                         {1.5, 0.},


                                         {-1.5, 1.5},
                                         {-0.5, 1.5},
                                         {0.5, 1.5},
                                         {1.5, 1.5},


                                         {-1.5, 3.},
                                         {-0.5, 3.},
                                         {0.5, 3.},
                                         {1.5, 3.},


                                         {-0.5, 3 + 0.5 * sqrt(3)},
                                         {0.5, 3 + 0.5 * sqrt(3)},


                                         {-0.75, 3 + 0.75 * sqrt(3)},
                                         {0.75, 3 + 0.75 * sqrt(3)}};


  const std::vector<std::array<unsigned int, GeometryInfo<2>::vertices_per_cell>>
    cell_vertices_1 = {{{0, 1, 4, 5}},
                       {{1, 2, 5, 6}},
                       {{3, 7, 2, 6}},
                       {{4, 5, 8, 9}},
                       {{5, 6, 9, 10}},
                       {{7, 11, 6, 10}},
                       {{8, 9, 14, 12}},
                       {{9, 10, 12, 13}},
                       {{11, 15, 10, 13}},
                       {{14, 12, 15, 13}}};


  // Copy vertices into a 2d triangulation
  Triangulation<2> triangulation_2d_1;
  create_2d_grid(vertices_1, cell_vertices_1, triangulation_2d_1);


  // Then extrude it into a 3d piece
  Triangulation<3> triangulation_3d_1;
  GridGenerator::extrude_triangulation(triangulation_2d_1,
                                       5,
                                       2.5,
                                       triangulation_3d_1);


  // Now do the same with the second volume
  const std::vector<Point<2>> vertices_2{{-2.5, 0.},
                                         {-1.5, 0.},
                                         {-0.5, 0.},
                                         {0.5, 0.},
                                         {1.5, 0.},
                                         {2.5, 0.},


                                         {-2.5, 1.5},
                                         {-1.5, 1.5},
                                         {-0.5, 1.5},
                                         {0.5, 1.5},
                                         {1.5, 1.5},
                                         {2.5, 1.5},


                                         {-2.5, 3.},
                                         {-1.5, 3.},
                                         {-0.5, 3.},
                                         {0.5, 3.},
                                         {1.5, 3.},
                                         {2.5, 3.},


                                         {-0.5, 3. + 0.5 * sqrt(3)},
                                         {0.5, 3. + 0.5 * sqrt(3)},


                                         {-0.75, 3. + 0.75 * sqrt(3)},
                                         {0.75, 3. + 0.75 * sqrt(3)},


                                         {-1.25, 3. + 1.25 * sqrt(3)},
                                         {1.25, 3. + 1.25 * sqrt(3)}};


  const std::vector<std::array<unsigned int, GeometryInfo<2>::vertices_per_cell>>
    cell_vertices_2 = {{{0, 1, 6, 7}},
                       {{1, 2, 7, 8}},
                       {{2, 3, 8, 9}},
                       {{4, 10, 3, 9}},
                       {{5, 11, 4, 10}},
                       {{6, 7, 12, 13}},
                       {{7, 8, 13, 14}},
                       {{8, 9, 14, 15}},
                       {{10, 16, 9, 15}},
                       {{11, 17, 10, 16}},
                       {{12, 13, 22, 20}},
                       {{13, 14, 20, 18}},
                       {{14, 15, 18, 19}},
                       {{16, 21, 15, 19}},
                       {{17, 23, 16, 21}},
                       {{20, 18, 21, 19}},
                       {{22, 20, 23, 21}}};


  Triangulation<2> triangulation_2d_2;
  create_2d_grid(vertices_2, cell_vertices_2, triangulation_2d_2);


  Triangulation<3> triangulation_3d_2;
  GridGenerator::extrude_triangulation(triangulation_2d_2,
                                       5,
                                       2.5,
                                       triangulation_3d_2);


  // Also shift this triangulation in the z-direction so that it matches the
  // end face of the first part
  GridTools::shift(Point<3>(0, 0, 2.5), triangulation_3d_2);


  // Now first merge these two pieces, then shift the first piece in
  // z-direction beyond the second, and merge the shifted piece with the two
  // previously merged one into the final one:
  Triangulation<3> triangulation_3d_tmp;
  GridGenerator::merge_triangulations(triangulation_3d_1,
                                      triangulation_3d_2,
                                      triangulation_3d_tmp);


  GridTools::shift(Point<3>(0, 0, 5), triangulation_3d_1);


  GridGenerator::merge_triangulations(triangulation_3d_tmp,
                                      triangulation_3d_1,
                                      triangulation);
}
@endcode



这就形成了以下的网格。

<img src="https://www.dealii.org/images/steps/developer/step-49.yuhan.8.png" alt="" width="400" height="355">

这个网格具有正确的一般形状，但是顶部的单元现在是多边形的：它们的边缘不再是沿着圆的，我们没有非常准确地表示原始几何形状。下一步是教给域的顶部部分，它应该是弯曲的。换句话说，所有在顶部边界单元上进行的计算都应该以圆柱坐标而不是笛卡尔坐标进行。我们可以通过创建一个CylindricalManifold对象并将其与上面的单元格相关联来做到这一点  $y = 3$  。这样，当我们细化上面的单元时，我们将沿着同心圆而不是直线来放置新的点。

在deal.II中，我们用继承自Manifold的类来描述所有的几何体。默认的几何图形是笛卡尔的，在FlatManifold类中实现。顾名思义，Manifold及其继承类提供了一种用微分几何的思想和术语来描述曲线和曲线单元的一般方法：例如，CylindricalManifold继承自ChartManifold，它通过回拉和前推来描述几何体。一般来说，人们应该认为Triangulation类描述了一个域的拓扑结构（当然，除了存储顶点的位置之外），而Manifold类描述了一个域的几何结构（例如，一对顶点是否位于圆弧或直线上）。Triangulation将通过对与该单元相关的Manifold进行计算来细化单元，而不管该单元是否在边界上。换句话说：Manifold类不需要任何关于Triangulation边界实际位置的信息：由Triangulation来查询正确的Manifold，以便对单元格进行计算。大多数的Manifold函数（例如， Manifold::get_intermediate_point) ）对域本身一无所知，只是假设给它的点是沿着测地线的。在这种情况下，在下面构建的CylindricalManifold中，测地线是沿正交于 $z$ 轴的圆弧，以直线 $(0, 3, z)$ 为中心。

由于领域的三个顶部部分都使用相同的测地线，我们将把所有中心在 $y = 3$ 线以上的单元格标记为圆柱形的性质。

@code
const Tensor<1, 3>           axis({0.0, 0.0, 1.0});
const Point<3>               axial_point(0, 3.0, 0.0);
const CylindricalManifold<3> cylinder(axis, axial_point);
const types::manifold_id     cylinder_id = 8;


Triangulation<3> triangulation;
create_3d_grid(triangulation);
triangulation.set_manifold(cylinder_id, cylinder);


for (auto &cell : triangulation.active_cell_iterators())
  if (cell->center()[1] >= 3.0)
    cell->set_all_manifold_ids(cylinder_id);


triangulation.refine_global(1);
@endcode



通过这段代码，我们得到一个看起来像这样的网格。

<img src="https://www.dealii.org/images/steps/developer/step-49.yuhan.9.png" alt="" width="400" height="355">

这一变化修复了边界，但产生了一个新的问题：与圆柱体轴线相邻的单元格严重扭曲。我们应该使用笛卡尔坐标对这些中心单元进行计算以避免这个问题。沿着中心线的单元格都有一个面接触到线 $(0, 3, z)$ ，所以，为了实现这一点，我们回去把这些单元格上的 <code>manifold_id</code> s改写为0（这是默认的）。

@code
const Tensor<1, 3>           axis({0.0, 0.0, 1.0});
const Point<3>               axial_point(0, 3.0, 0.0);
const CylindricalManifold<3> cylinder(axis, axial_point);
const types::manifold_id     cylinder_id = 8;


Triangulation<3> triangulation;
create_3d_grid(triangulation);
triangulation.set_manifold(cylinder_id, cylinder);


for (auto &cell : triangulation.active_cell_iterators())
  if (cell->center()[1] >= 3.0)
    cell->set_all_manifold_ids(cylinder_id);


for (const auto &cell : triangulation.active_cell_iterators())
  for (const auto &face : cell->face_iterators())
    {
      const Point<3> face_center = face->center();
      if (std::abs(face_center[0]) < 1.0e-5 &&
          std::abs(face_center[1] - 3.0) < 1.0e-5)
        cell->set_all_manifold_ids(numbers::flat_manifold_id);
    }


triangulation.refine_global(1);
@endcode



这给了我们以下的网格。

<img src="https://www.dealii.org/images/steps/developer/step-49.yuhan.10.png" alt="" width="400" height="355">

这给了我们一个很好的网格，每个圆心的单元仍然是笛卡尔的，而边界周围的单元是沿着圆的。如果我们再细化两次，我们可以真正看到边界拟合网格的良好细节。

<img src="https://www.dealii.org/images/steps/developer/step-49.yuhan.11.png" alt="" width="400" height="355">




<a name="Possibilitiesforextensions"></a><h3> Possibilities for extensions </h3>


<a name="Assigningdifferentboundaryids"></a><h4> Assigning different boundary ids </h4>


为本教程中描述的以某种形式生成的网格分配不同的边界ID，以应用不同的边界条件，通常是很有用的。

例如，你可能想对这个程序中第一个网格的右边边界应用不同的边界条件。要做到这一点，遍历单元格和它们的面，确定正确的面（例如使用`cell->center()`来查询单元格中心的坐标，就像我们在步骤1中做的那样，或者使用`cell->face(f)->get_boundary_id()`来查询该单元格第 $f$ 个面的当前边界指标）。然后你可以使用`cell->face(f)->set_boundary_id()`来设置边界指标为不同的内容。你可以回顾一下步骤1，看看网格的迭代是如何进行的。

<a name="Extractingaboundarymesh"></a><h4> Extracting a boundary mesh </h4>


在流形上的计算，就像在step-38中做的那样，需要一个嵌入到高维空间的曲面网格。虽然有些网格可以用GridGenerator命名空间来构建或者从文件中加载，但有时从体积网格中提取一个表面网格也是很有用的。

使用函数  GridGenerator::extract_boundary_mesh()  来提取网格的表面元素。在一个三维网格上使用这个函数（一个`三角网格<3,3>`，例如从`grid_4()`），这将返回一个`三角网格<2,3>`，你可以在步骤38中使用。  也可以尝试提取一个`三角网格<2,2>`的边界网格。


<!--

本教程可能的扩展。

- 用于收敛研究的非结构化网格数据库

- 如何删除或禁用网格内的一个单元格

-->


 *
 *
<a name="PlainProg"></a>
<h1> The plain program</h1>
@include "step-49.cc"
*/
